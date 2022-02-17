/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-d <gcosta-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 21:57:10 by gcosta-d          #+#    #+#             */
/*   Updated: 2022/02/17 01:26:47 by gcosta-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/pipex_bonus.h"

void	handle_errors(int signal)
{
	if (signal == 0)
		errno = EINVAL;
	else if (signal == 1)
		errno = ENOENT;
	else if (signal == 2)
		errno = EPIPE;
	else if (signal == 3)
		errno = ESRCH;
	else if (signal == 4)
	{
		perror("command not found");
		exit(127);
	}
	else if (signal == 5)
		errno = ENOMEM;
	else if (signal == 6)
		errno = ENOEXEC;
	perror("ERROR");
	exit(EXIT_FAILURE);
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
