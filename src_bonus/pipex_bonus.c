/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-d <gcosta-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 02:51:14 by gcosta-d          #+#    #+#             */
/*   Updated: 2022/01/03 21:11:59 by gcosta-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/pipex_bonus.h"

void	pipex_in(t_data *data, char *envp[])
{
	data->pid_1 = fork();
	if (data->pid_1 == -1)
		handle_errors(3, data);
	if (data->pid_1 == 0)
	{
		dup2(data->file_in, STDIN_FILENO);
		dup2(data->fd[1], STDOUT_FILENO);
		close(data->fd[0]);
		close(data->fd[1]);
		close(data->file_in);
		close(data->file_out);
		execve(data->file_path[0], data->arg1, envp);
	}
}

void	pipex_out(t_data *data, char *envp[])
{
	data->pid_2 = fork();
	if (data->pid_2 == -1)
		handle_errors(3, data);
	if (data->pid_2 == 0)
	{
		dup2(data->fd[0], STDIN_FILENO);
		dup2(data->file_out, STDOUT_FILENO);
		close(data->fd[0]);
		close(data->fd[1]);
		close(data->file_in);
		close(data->file_out);
		execve(data->file_path[0], data->arg2, envp);
	}
}
