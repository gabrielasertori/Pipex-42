/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-d <gcosta-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 21:57:10 by gcosta-d          #+#    #+#             */
/*   Updated: 2022/01/17 16:15:20 by gcosta-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/pipex_bonus.h"

void	handle_errors(int signal, t_data *data)
{
	if (signal == 0)
	{
		ft_putendl_fd("\e[0;31mInvalid arguments\e[0m", 2);
		exit (0);
	}
	if (signal == 1)
		ft_putendl_fd("\e[0;31mNot a valid infile\e[0m", 2);
	if (signal == 2)
		ft_putendl_fd("\e[0;31mPipe doesn't work\e[0m", 2);
	if (signal == 3)
		ft_putendl_fd("\e[0;31mFork doesn't work\e[0m", 2);
	if (signal == 4)
	{
		ft_putendl_fd("\e[0;31mCommand doesn't found\e[0m", 2);
		exit(127);
	}
	if (signal == 5)
		ft_putendl_fd("\e[0;31mMalloc failed\e[0m", 2);
	printf("%d\n", data->qnt_cmds);
	exit(0);
	//free_exit(data);
}

void	free_exit(t_data *data)
{
	int i;

	i = 0;
	if (data->file_path)
		free_matrix(data->file_path);
	if (data->args)
	{
		while (data->cmds)
		{
			free_matrix(data->args[i]);
			i++;
			data->cmds--;
		}
		free(data->args);
	}
	exit(0);
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
