/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-d <gcosta-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 21:57:10 by gcosta-d          #+#    #+#             */
/*   Updated: 2021/12/21 23:54:36 by gcosta-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	handle_errors(int signal, t_data *data)
{
	if (signal == 0)
		ft_putendl_fd("\e[0;31mFew arguments\e[0m", 1);
	if (signal == 1)
		ft_putendl_fd("\e[0;31mNot a valid infile\e[0m", 1);
	if (signal == 2)
		ft_putendl_fd("\e[0;31mPipe doesn't work\e[0m", 1);
	if (signal == 3)
		ft_putendl_fd("\e[0;31mFork doesn't work\e[0m", 1);
	if (signal == 4)
		ft_putendl_fd("\e[0;31mNot a valid outfile\e[0m", 1);
	if (signal == 5)
		ft_putendl_fd("\e[0;31mMalloc fails\e[0m", 1);
	free_exit(data);
}