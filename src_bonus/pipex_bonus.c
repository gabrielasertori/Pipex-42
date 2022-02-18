/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-d <gcosta-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 02:51:14 by gcosta-d          #+#    #+#             */
/*   Updated: 2022/02/18 01:10:27 by gcosta-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/pipex_bonus.h"

static void	exec_commands(t_data *data, int index, char *argv[], char *envp[]);
static void	resolve_dups(t_data *data, int index);
static int	generate_pipe(t_data *data, char *argv[], char *envp[]);

int	pipex(t_data *data, char *argv[], char *envp[])
{
	int	status;

	dup2(data->file_in, STDIN_FILENO);
	close(data->file_in);
	status = generate_pipe(data, argv, envp);
	close(data->file_out);
	close(data->fd[0]);
	close(data->fd[1]);
	unlink("hdoc_file");
	return (status);
}

static int	generate_pipe(t_data *data, char *argv[], char *envp[])
{
	int	index;

	index = 0;
	while (index < data->qnt_cmds)
	{
		if (index > 0)
		{
			dup2(data->fd[0], STDIN_FILENO);
			close(data->fd[0]);
		}
		if (pipe(data->fd) == -1)
			handle_errors(2);
		data->pid = fork();
		if (data->pid == -1)
			handle_errors(3);
		if (data->pid == 0)
			exec_commands(data, index, argv, envp);
		else
		{
			waitpid(data->pid, &data->status, 0);
			close(data->fd[1]);
			index++;
		}
	}
	return (WEXITSTATUS(data->status));
}

static void	exec_commands(t_data *data, int index, char *argv[], char *envp[])
{
	if (data->heredoc == 1)
		parse_argv(data, argv[index + 3]);
	else
		parse_argv(data, argv[index + 2]);
	data->file_path = command_finder(data->cmd_parsed[0]);
	if (data->file_path == NULL)
	{
		free_matrix(data->cmd_parsed);
		free(data->file_path);
		handle_errors(4);
	}
	resolve_dups(data, index);
	if (execve(data->file_path, data->cmd_parsed, envp) == -1)
	{
		free_matrix(data->cmd_parsed);
		free(data->file_path);
		handle_errors(6);
	}
}

static void	resolve_dups(t_data *data, int index)
{
	if (index == data->qnt_cmds - 1)
	{
		dup2(data->file_out, STDOUT_FILENO);
		close(data->file_out);
	}
	else
	{
		dup2(data->fd[1], STDOUT_FILENO);
		close(data->fd[1]);
	}
}
