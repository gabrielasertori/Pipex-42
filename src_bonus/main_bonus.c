/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-d <gcosta-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 21:05:58 by gcosta-d          #+#    #+#             */
/*   Updated: 2022/01/03 23:09:31 by gcosta-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/pipex_bonus.h"

static void	parse_args(t_data *data);
static void	open_files(t_data *data, char *argv[]);

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;
	int		i;

	if (argc < 5)
		handle_errors(0, &data);
	else
		init_args(argc, argv, &data);
	open_files(&data, argv);
	parse_args(&data);

	data.pipe_ok = pipe(data.fd);
	if (data.pipe_ok == -1)
		handle_errors(2, &data);

	data.pid = fork();
	if (data.pid == -1)
		handle_errors(3, &data);

	i = 0;
	pipex(&data, envp, i);

	waitpid(data.pid, NULL, 0);
	free_exit(&data);
	return (0);
}

static void	open_files(t_data *data, char *argv[])
{
	if (data->file1)
	{
		data->file_in = open(data->file1, O_RDONLY);
		if (data->file_in == -1)
			handle_errors(1, data);
	}
	if (ft_strnstr(argv[1], "here_doc", 8))
		data->file_out = open(data->file2, O_WRONLY | O_CREAT | O_APPEND, 0744);
	else
		data->file_out = open(data->file2, O_WRONLY | O_CREAT | O_TRUNC, 0744);
	if (data->file_out == -1)
		handle_errors(4, data);
}

static void	parse_args(t_data *data)
{
	int	i;
	int	cmds;

	i = 0;
	cmds = data->qnt_cmds;
	data->args = malloc(sizeof(char ***));
	data->file_path = malloc(sizeof(char **));
	while (cmds)
	{
		if (treat_space(data->cmds[i]))
			data->args[i] = ft_split(data->cmds[i], ';');
		else
			data->args[i] = ft_split(data->cmds[i], ' ');
		data->file_path[i] = file_found(data->args[i][0]);
		if (!data->file_path[i])
			handle_errors(4, data);
		i++;
		cmds--;
	}
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
		free(command_path);
		i++;
	}
	free_matrix(paths);
	return (NULL);
}
