/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-d <gcosta-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 02:51:14 by gcosta-d          #+#    #+#             */
/*   Updated: 2022/01/04 03:00:12 by gcosta-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/pipex_bonus.h"

static void	execute_commands(t_data *data, char *envp[], int i, int cmd);
static void	resolve_dups(t_data *data, int cmd);

// file1 "grep Teste" <-> "wc -l" <-> "cat" file2
// qnt de pipes == qnt_cmds - 1

void	pipex(t_data *data, char *envp[])
{
	int	cmds;
	int	i;

	cmds = data->qnt_cmds;
	i = 0;
	data->pipe_ok = pipe(data->fd);
	if (data->pipe_ok == -1)
		handle_errors(2, data);

	data->pid[i] = fork();
	if (data->pid[i] == -1)
		handle_errors(3, data);
	if (data->pid[i] == 0)
		execute_commands(data, envp, i, cmds);
	cmds--;
	i++;
	data->pid[i] = fork();
	if (data->pid[i] == -1)
		handle_errors(3, data);
	if (data->pid[i] == 0)
		execute_commands(data, envp, i, cmds);

	waitpid(data->pid[0], NULL, 0);

}

static void	execute_commands(t_data *data, char *envp[], int i, int cmd)
{
	resolve_dups(data, cmd);
	close(data->fd[0]);
	close(data->fd[1]);
	close(data->file_in);
	close(data->file_out);
	execve(data->file_path[i], data->args[i], envp);
}

static void	resolve_dups(t_data *data, int cmds)
{
	if (cmds == data->qnt_cmds && data->heredoc != 1)
	{
		dup2(data->file_in, STDIN_FILENO);
		dup2(data->fd[1], STDOUT_FILENO);
	}
	else if (cmds == 1)
	{
		dup2(data->fd[0], STDIN_FILENO);
		dup2(data->file_out, STDOUT_FILENO);
	}
	else
	{
		dup2(data->fd[0], STDIN_FILENO);
		dup2(data->fd[1], STDOUT_FILENO);
	}
}

// file1 -> "grep Teste" -> fd[1]===fd[0] -> "wc -l" -> fd[1]===fd[0] -> "cat" -> file2
