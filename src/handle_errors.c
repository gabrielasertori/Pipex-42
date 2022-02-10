/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-d <gcosta-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 21:57:10 by gcosta-d          #+#    #+#             */
/*   Updated: 2022/02/10 01:38:45 by gcosta-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/pipex_bonus.h"

static void	close_remain_fds(t_data *data);

void	handle_errors(int signal, t_data *data)
{
	if (signal == 0 || signal == 4)
		errno = EINVAL;
	else if (signal == 1)
		errno = ENOENT;
	else if (signal == 2)
		errno = EPIPE;
	else if (signal == 3)
		errno = ESRCH;
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
