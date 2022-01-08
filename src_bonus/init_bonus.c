/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-d <gcosta-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 18:39:22 by gcosta-d          #+#    #+#             */
/*   Updated: 2022/01/04 14:34:34 by gcosta-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/pipex_bonus.h"

void	init_args(int argc, char *argv[], t_data *data)
{
	if (argc == 6 && ft_strnstr(argv[1], "here_doc", 8))
		init_hdoc_args(argv, data);
	init_multi_args(argc, argv, data);
}

void	init_hdoc_args(char *argv[], t_data *data)
{
	data->heredoc = 1;
	data->limiter = argv[2];
	data->file2 = argv[5];
}

/* qnt_cmds = quantity of argcs - 3, (./pipex, file1 and file2) */
void	init_multi_args(int argc, char *argv[], t_data *data)
{
	int	cmds;
	int	i;
	int	j;

	if (data->heredoc == 1)
		data->qnt_cmds = 2;
	else
	{
		data->qnt_cmds = argc - 3;
		data->file1 = argv[1];
	}
	data->file2 = argv[argc - 1];
	cmds = data->qnt_cmds;
	data->cmds = malloc(sizeof(char **) * data->qnt_cmds);
	i = 0;
	j = 2;
	if (data->heredoc == 1)
		j++;
	while (cmds)
	{
		data->cmds[i] = argv[j];
		i++;
		j++;
		cmds--;
	}
}
