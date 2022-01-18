/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-d <gcosta-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 21:57:10 by gcosta-d          #+#    #+#             */
/*   Updated: 2022/01/18 21:56:17 by gcosta-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/pipex_bonus.h"

static void	close_remain_fds(t_data *data);

void	handle_errors(int signal, t_data *data)
{
	close_remain_fds(data);
	if (signal == 0)
		write(2, "\e[0;31mInvalid number of arguments\e[0m", 28);
	else if (signal == 1)
		write(2, "\e[0;31mNot a valid file\e[0m", 27);
	else if (signal == 2)
		write(2, "\e[0;31mPipe doesn't work\e[0m", 29);
	else if (signal == 3)
		write(2, "\e[0;31mFork doesn't work\e[0m", 29);
	else if (signal == 4)
		write(2, "\e[0;31mCommand doesn't found\e[0", 31);
	else if (signal == 5)
		write(2, "\e[0;31mMalloc failed\e[0m", 25);
	else if (signal == 6)
		write(2, "\e[0;31mExecve failed\e[0m", 25);
	exit(0);
}

static void	close_remain_fds(t_data *data)
{
	if (data->file_in)
		close(data->file_in);
	if (data->file_in)
		close(data->file_out);
	if (data->fd[0])
		close(data->fd[0]);
	if (data->fd[1])
		close(data->fd[1]);
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
	matrix = NULL;
}
