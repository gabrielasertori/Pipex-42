/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-d <gcosta-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 18:39:22 by gcosta-d          #+#    #+#             */
/*   Updated: 2022/01/19 17:19:47 by gcosta-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/pipex_bonus.h"

void	init_args(int argc, char *argv[], t_data *data)
{
	data->qnt_cmds = argc - 3;
	data->file2 = argv[argc - 1];
	data->file1 = argv[1];
	if (argc >= 6 && ft_strnstr(argv[1], "here_doc", 8) != NULL)
	{
		data->heredoc = 1;
		data->limiter = argv[2];
		data->qnt_cmds = argc - 4;
	}
}
