/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-d <gcosta-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 02:51:14 by gcosta-d          #+#    #+#             */
/*   Updated: 2022/01/03 23:00:00 by gcosta-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/pipex_bonus.h"

void	pipex(t_data *data, char *envp[], int i)
{
	if (data->pid == 0)
	{
		dup2(data->file_in, STDIN_FILENO);
		dup2(data->fd[1], STDOUT_FILENO);
		close(data->fd[0]);
		close(data->fd[1]);
		close(data->file_in);
		close(data->file_out);
		execve(data->file_path[i], data->args[i], envp);
	}
	else
	{
		dup2(data->file_out, STDOUT_FILENO);
		dup2(data->fd[0], STDIN_FILENO);
		close(data->fd[0]);
		close(data->fd[1]);
		close(data->file_in);
		close(data->file_out);
		execve(data->file_path[i + 1], data->args[i + 1], envp);
	}
}
