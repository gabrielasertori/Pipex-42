/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-d <gcosta-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 02:51:14 by gcosta-d          #+#    #+#             */
/*   Updated: 2022/01/18 21:24:18 by gcosta-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/pipex_bonus.h"

static void	execute_commands(t_data *data, int index, char *argv[], char *envp[]);
static void	resolve_dups(t_data *data, int index);

void	pipex(t_data *data, char *argv[], char *envp[])
{
	int	index;

	index = 0;
	dup2(data->file_in, STDIN_FILENO);
	while (index < data->qnt_cmds)
	{
		if (index > 0)
			dup2(data->fd[0], STDIN_FILENO);
		if (pipe(data->fd) == -1)
			handle_errors(2, data);
		data->pid = fork();
		if (data->pid == -1)
			handle_errors(3, data);
		if (data->pid == 0)
		{
			close(data->fd[0]);
			execute_commands(data, index, argv, envp);
		}
		else
		{
			waitpid(data->pid, NULL, 0);
			close(data->fd[1]);
			index++;
		}
	}
	close(data->file_out);
}

static void	execute_commands(t_data *data, int index, char *argv[], char *envp[])
{
	char	**command_parsed;

	command_parsed = parse_argv(data, argv[index + 2]);
	data->file_path = command_finder(command_parsed[0]);
	if (data->file_path == NULL)
		handle_errors(4, data);
	resolve_dups(data, index);
	if (execve(data->file_path, command_parsed, envp) == -1)
		handle_errors(6, data);
}

static void	resolve_dups(t_data *data, int index)
{
	if (index == data->qnt_cmds - 1)
		dup2(data->file_out, STDOUT_FILENO);
	else
		dup2(data->fd[1], STDOUT_FILENO);
}
