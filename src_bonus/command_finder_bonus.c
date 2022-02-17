/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_finder_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-d <gcosta-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:26:43 by gcosta-d          #+#    #+#             */
/*   Updated: 2022/02/17 01:28:08 by gcosta-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/pipex_bonus.h"

static int	is_path_bin(char *command);

char	*command_finder(char *command)
{
	char	**paths;
	char	*command_path;
	int		i;

	i = 0;
	if (is_path_bin(command))
		return (command);
	paths = ft_split(VALID_PATHS, ':');
	while (paths[i])
	{
		command_path = ft_strjoin(paths[i], command);
		if (!access(command_path, F_OK))
		{
			free_matrix(paths);
			return (command_path);
		}
		i++;
		free(command_path);
	}
	free_matrix(paths);
	return (NULL);
}

static int	is_path_bin(char *command)
{
	int	is_path;

	is_path = 0;
	if (!access(command, F_OK))
		is_path = 1;
	return (is_path);
}
