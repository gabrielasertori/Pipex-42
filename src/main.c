/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-d <gcosta-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 21:05:58 by gcosta-d          #+#    #+#             */
/*   Updated: 2021/12/16 15:37:10 by gcosta-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	init_args(char *argv[], t_data *data);

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;

	if (argc < 5)
		handle_errors(0);

	parse_args(argv, &data);

	data.file1 = argv[1];
	data.file2 = argv[4];

	data.pipe_ok = pipe(data.fd);
	if (data.pipe_ok == -1)
		handle_errors(2);

	data.file_in = open(data.file1, O_RDONLY);
	if (data.file_in == -1)
		handle_errors(1);

	data.pid_1 = fork();
	if (data.pid_1 == -1)
		handle_errors(3);
	if (data.pid_1 == 0)
	{
		dup2(data.file_in, STDIN_FILENO);
		dup2(data.fd[1], STDOUT_FILENO);
		close(data.file_in);
		execve("/usr/bin/cat", arv1, envp);
	}
	close(data.fd[1]);

	data.file_out = open(data.file2, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (data.file_in == -1)
		handle_errors(1);

	data.pid_2 = fork();
	if (data.pid_2 == -1)
		handle_errors(3);
	if (data.pid_2 == 0)
	{
		waitpid(data.pid_1, NULL, 0);
		dup2(data.fd[0], STDIN_FILENO);
		dup2(data.file_out, STDOUT_FILENO);
		close(data.file_out);
		execve("/usr/bin/cat", arv2, envp);
	}
	close(data.fd[0]);

	waitpid(data.pid_2, NULL, 0);

	return (0);
}

void	parse_args(char *argv[], t_data *data)
{

}

// ./pipex file1 "grep This" "wc -l" file2
//	[0]		[1]		[2]			[3]		[4]