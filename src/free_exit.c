/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-d <gcosta-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 23:52:28 by gcosta-d          #+#    #+#             */
/*   Updated: 2021/12/22 00:01:07 by gcosta-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_exit(t_data *data)
{
	free_matrix(data);
}

void	free_matrix(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->cmds_list)
	{
		free(data->cmds[i]);
		i++;
	}
	free(data->cmds);
}