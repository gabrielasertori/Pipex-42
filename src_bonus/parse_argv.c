/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-d <gcosta-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 21:24:01 by gcosta-d          #+#    #+#             */
/*   Updated: 2022/01/20 01:22:24 by gcosta-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/pipex_bonus.h"

static int	treat_space(char *command);

char	**parse_argv(char *command)
{
	char	**command_parsed;

	if (treat_space(command))
		command_parsed = ft_split(command, ';');
	else
		command_parsed = ft_split(command, ' ');
	return (command_parsed);
}

static int	treat_space(char *command)
{
	int	is_space;
	int	i;

	is_space = 0;
	i = 0;
	if (ft_strnstr(command, "' ", ft_strlen(command)))
	{
		is_space = 1;
		while (command[i] != '\0')
		{
			if (command[i] == ' ')
				command[i] = ';';
			else if (command[i] == '\'' && command[i + 1] == ' ')
			{
				command[i] = ';';
				i++;
				while (command[i] == ' ')
					i++;
				command[i] = ';';
			}
			i++;
		}
	}
	return (is_space);
}
