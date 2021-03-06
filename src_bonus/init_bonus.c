/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-d <gcosta-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 18:39:22 by gcosta-d          #+#    #+#             */
/*   Updated: 2022/02/09 23:40:14 by gcosta-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/pipex_bonus.h"

void	init_args(int argc, char *argv[], t_data *data)
{
	data->qnt_cmds = argc - 3;
	data->file2 = argv[argc - 1];
	data->file1 = argv[1];
	data->heredoc = 0;
	if (argc >= 6 && ft_strncmp(argv[1], "here_doc", 8))
	{
		data->heredoc = 1;
		data->limiter = argv[2];
		data->qnt_cmds = argc - 4;
	}
}
