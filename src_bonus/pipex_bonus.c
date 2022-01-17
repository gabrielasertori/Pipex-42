/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-d <gcosta-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 02:51:14 by gcosta-d          #+#    #+#             */
/*   Updated: 2022/01/17 18:23:53 by gcosta-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/pipex_bonus.h"

static void	execute_commands(t_data *data, char *envp[], int fd[], int index);
static void	resolve_dups(t_data *data, int fd[], int index);

void	pipex(t_data *data, char *envp[])
{
	int	index;
	int	fd[2];
	int	pid;

	index = 0;
	while (index < data->qnt_cmds)
	{
		if (index < data->qnt_cmds - 1)
		{
			data->pipe_ok = pipe(fd);
			if (data->pipe_ok == -1)
				handle_errors(2, data);
		}
		pid = fork();
		if (pid == -1)
			handle_errors(3, data);
		if (pid == 0)
			execute_commands(data, envp, fd, index);
		waitpid(pid, NULL, 0);
		close(fd[1]);
		index++;
	}
	close(data->file_in);
	close(data->file_out);
}

static void	execute_commands(t_data *data, char *envp[], int fd[], int index)
{
	resolve_dups(data, fd, index);
	execve(data->file_path[index], data->args[index], envp);
}

static void	resolve_dups(t_data *data, int fd[], int index)
{
	if (index == 0)
	{
		dup2(data->file_in, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		write(2, "hey\n", 4);
	}
	else if (index == data->qnt_cmds - 1)
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(data->file_out, STDOUT_FILENO);
		write(2, "Lets go\n", 8);
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		write(2, "ho\n", 3);
	}
}
/*
void	pipex(t_data *data, char *envp[])
{
	int	cmds;
	int	i;
	int	pid;

	cmds = data->qnt_cmds;
	i = 0;
	while (cmds)
	{
		if (i == 0)
		{
			data->pipe_ok = pipe(data->fd);
			if (data->pipe_ok == -1)
				handle_errors(2, data);
		}
		else if (data->qnt_cmds > 2 && i % 2 != 0)
		{
			data->pipe_ok = pipe(data->new_fd);
			if (data->pipe_ok == -1)
				handle_errors(2, data);
		}
		pid = fork();
		if (pid == -1)
			handle_errors(3, data);
		if (pid == 0)
			execute_commands(data, envp, i, cmds);
		waitpid(pid, NULL, 0);
		if (i == 0)
			close(data->fd[1]);
		else if (data->qnt_cmds > 2 && i % 2 != 0)
			close(data->new_fd[1]);
		cmds--;
		i++;
	}
	close(data->file_in);
	close(data->file_out);
}

static void	execute_commands(t_data *data, char *envp[], int i, int cmd)
{
	resolve_dups(data, cmd);
	execve(data->file_path[i], data->args[i], envp);
}

static void	resolve_dups(t_data *data, int cmds)
{
	if (cmds == data->qnt_cmds && data->heredoc != 1)
	{
		dup2(data->file_in, STDIN_FILENO);
		dup2(data->fd[1], STDOUT_FILENO);
		write(2, "hey\n", 4);
	}
	else if (cmds == 1 || data->qnt_cmds == 2)
	{
		dup2(data->fd[0], STDIN_FILENO);
		dup2(data->file_out, STDOUT_FILENO);
		close(data->fd[1]);
		write(2, "Lets go\n", 8);
	}
	else if (cmds == 1)
	{
		dup2(data->new_fd[0], STDIN_FILENO);
		dup2(data->file_out, STDOUT_FILENO);
		close(data->new_fd[1]);
		write(2, "oo\n", 8);
	}
	else
	{
		dup2(data->fd[0], STDIN_FILENO);
		dup2(data->new_fd[1], STDOUT_FILENO);
		close(data->fd[0]);
		write(2, "ho\n", 3);
	}
}
*/