/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_finder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-d <gcosta-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:26:43 by gcosta-d          #+#    #+#             */
/*   Updated: 2022/01/18 21:54:27 by gcosta-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/pipex_bonus.h"

char	*command_finder(char *command)
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
