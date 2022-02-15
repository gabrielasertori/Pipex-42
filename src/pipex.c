/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-d <gcosta-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 02:51:14 by gcosta-d          #+#    #+#             */
/*   Updated: 2022/02/15 03:16:25 by gcosta-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	exec_commands(t_data *data, int index, char *argv[], char *envp[]);
static void	resolve_dups(t_data *data, int index);
static void	generate_pipe(t_data *data, char *argv[], char *envp[]);

void	pipex(t_data *data, char *argv[], char *envp[])
{
	dup2(data->file_in, STDIN_FILENO);
	generate_pipe(data, argv, envp);
	close(data->file_in);
	close(data->file_out);
	close(data->fd[0]);
	close(data->fd[1]);
}

static void	generate_pipe(t_data *data, char *argv[], char *envp[])
{
	int	index;
	int	status;

	index = 0;
	while (index < 2)
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
			waitpid(data->pid, &status, 0);
			close(data->fd[1]);
			index++;
		}
	}
}

static void	exec_commands(t_data *data, int index, char *argv[], char *envp[])
{
	char	**command_parsed;

	command_parsed = parse_argv(data, argv[index + 2]);
	data->file_path = command_finder(command_parsed[0]);
	if (data->file_path == NULL)
	{
		free_matrix(command_parsed);
		free(data->file_path);
		handle_errors(4);
	}
	resolve_dups(data, index);
	if (execve(data->file_path, command_parsed, envp) == -1)
	{
		free_matrix(command_parsed);
		free(data->file_path);
		handle_errors(6);
	}
}

static void	resolve_dups(t_data *data, int index)
{
	if (index == 1)
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
