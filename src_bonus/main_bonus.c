/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-d <gcosta-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 21:05:58 by gcosta-d          #+#    #+#             */
/*   Updated: 2022/01/20 15:32:12 by gcosta-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/pipex_bonus.h"

static int	open_files(t_data *data);

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;

	if (argc < 5)
		handle_errors(0, &data);
	else
		init_args(argc, argv, &data);
	open_files(&data);
	pipex(&data, argv, envp);
	exit(0);
}

static int	open_files(t_data *data)
{
	if (data->heredoc == 1)
	{
		here_doc(data);
		data->file_out = open(data->file2, O_WRONLY | O_CREAT | O_APPEND, 0744);
	}
	else
	{
		data->file_in = open(data->file1, O_RDONLY);
		data->file_out = open(data->file2, O_WRONLY | O_CREAT | O_TRUNC, 0744);
	}
	if (data->file_out == -1 || data->file_in == -1)
		handle_errors(1, data);
	return (0);
}
