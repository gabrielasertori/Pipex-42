/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-d <gcosta-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 21:05:58 by gcosta-d          #+#    #+#             */
/*   Updated: 2021/12/22 21:57:55 by gcosta-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	init_args(char *argv[], t_data *data);
static void	parse_args(t_data *data);
static void	open_files(t_data *data);

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;

	if (argc != 5)
		handle_errors(0, &data);
	init_args(argv, &data);
	parse_args(&data);
	open_files(&data);
	data.file_path = file_found(data.arg1[0]);
	if (!data.file_path)
		handle_errors(4, &data);
	pipex_in(&data, envp);
	free(data.file_path);
	// waitpid(data.pid_1, NULL, 0);
	data.file_path = file_found(data.arg2[0]);
	if (!data.file_path)
		handle_errors(4, &data);
	pipex_out(&data, envp);
	free(data.file_path);
	close(data.fd[0]);
	close(data.fd[1]);
	close(data.file_in);
	close(data.file_out);
	waitpid(data.pid_2, NULL, 0);
	free_exit(&data);
	return (0);
}

static void	init_args(char *argv[], t_data *data)
{
	data->file1 = argv[1];
	data->cmd1 = argv[2];
	data->cmd2 = argv[3];
	data->file2 = argv[4];
}

static void	parse_args(t_data *data)
{
	if (treat_space(data->cmd1))
		data->arg1 = ft_split(data->cmd1, ';');
	else
		data->arg1 = ft_split(data->cmd1, ' ');
	if (treat_space(data->cmd2))
		data->arg2 = ft_split(data->cmd2, ';');
	else
		data->arg2 = ft_split(data->cmd2, ' ');
}

static void	open_files(t_data *data)
{
	data->file_in = open(data->file1, O_RDONLY);
	if (data->file_in == -1)
		handle_errors(1, data);
	data->file_out = open(data->file2, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (data->file_out == -1)
		handle_errors(4, data);
	data->pipe_ok = pipe(data->fd);
	if (data->pipe_ok == -1)
		handle_errors(2, data);
}

char	*file_found(char *command)
{
	char	**paths;
	char	*command_path;
	int		i;

	i = 0;
	paths = ft_split(VALID_PATHS, ':');
	while (paths[i])
	{
		command_path = ft_strjoin(paths[i], command);
		if (!access(command_path, F_OK))
		{
			free_matrix(paths);
			return (command_path);
		}
		// free(paths[i]);
		free(command_path);
		i++;
	}
	return (NULL);
}
