/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-d <gcosta-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 21:05:58 by gcosta-d          #+#    #+#             */
/*   Updated: 2022/02/17 01:32:25 by gcosta-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	open_files(t_data *data);

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;
	int		status;

	if (argc < 5)
		handle_errors(0);
	init_args(argc, argv, &data);
	open_files(&data);
	status = pipex(&data, argv, envp);
	return (status);
}

static int	open_files(t_data *data)
{
	data->file_in = open(data->file1, O_RDONLY);
	data->file_out = open(data->file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->file_out == -1 || data->file_in == -1)
		handle_errors(1);
	return (0);
}
