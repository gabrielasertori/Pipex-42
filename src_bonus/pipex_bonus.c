/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-d <gcosta-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 02:51:14 by gcosta-d          #+#    #+#             */
/*   Updated: 2022/01/20 15:30:24 by gcosta-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/pipex_bonus.h"

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
	unlink("hdoc_file");
}

static void	generate_pipe(t_data *data, char *argv[], char *envp[])
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
			handle_errors(2, data);
		data->pid = fork();
		if (data->pid == -1)
			handle_errors(3, data);
		if (data->pid == 0)
			exec_commands(data, index, argv, envp);
		else
		{
			waitpid(data->pid, NULL, 0);
			close(data->fd[1]);
			index++;
		}
	}
	close(data->file_out);
}

static void	exec_commands(t_data *data, int index, char *argv[], char *envp[])
{
	char	**command_parsed;

	close(data->fd[0]);
	if (data->heredoc == 1)
		command_parsed = parse_argv(argv[index + 3]);
	else
		command_parsed = parse_argv(argv[index + 2]);
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
