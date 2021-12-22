/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-d <gcosta-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 21:05:58 by gcosta-d          #+#    #+#             */
/*   Updated: 2021/12/22 02:27:11 by gcosta-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	init_args(char *argv[], t_data *data);
static void	parse_args(char *argv[], t_data *data);
static void	open_files(t_data *data);

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;
	int	i;

	if (argc < 5)
		handle_errors(0, &data);
	data.cmds_list = argc - 3;
	init_args(argv, &data);
	parse_args(argv, &data);
	open_files(&data);
	data.pids = malloc(sizeof(int *) * data.cmds_list + 1);
	while (i < data.cmds_list)
	{
		fork_ncommands(i, &data, envp);
		waitpid(data.pids[i], NULL, 0);
		printf("TERMINOU\n");
		i++;
	}
	close(data.fd[0]);
	close(data.fd[1]);
	close(data.file_in);
	close(data.file_out);
	waitpid(data.pids[i], NULL, 0);

	return (0);
}

static void	init_args(char *argv[], t_data *data)
{
	int	i;
	int	j;

	i = 2;
	j = 0;
	data->cmds = malloc(sizeof(char **) + 1);
	if (!data->cmds)
		handle_errors(5, data);
	while (j < data->cmds_list)
	{
		data->cmds[j] = malloc(sizeof(char *));
		if (!data->cmds[j])
			handle_errors(5, data);
		data->cmds[j] = argv[i];
		i++;
		j++;
	}
	data->cmds[j] = '\0';
	data->file1 = argv[1];
	data->file2 = argv[i];
}

static void	parse_args(char *argv[], t_data *data)
{
	int	i;

	i = 0;
	data->args = malloc(sizeof(char ***));
	while (data->cmds[i])
	{
		data->args[i] = ft_split(data->cmds[i], ' ');
		i++;
	}
	data->args[i] = '\0';
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
			return (command_path);
		free(command_path);
		i++;
	}
	return (NULL);
}
