/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-d <gcosta-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 21:24:01 by gcosta-d          #+#    #+#             */
/*   Updated: 2022/02/10 03:32:28 by gcosta-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	change_char(t_data *data, char *command);
static int	treat_space(t_data *data, char *command);

char	**parse_argv(t_data *data, char *command)
{
	char	**command_parsed;

	if (treat_space(data, command))
		command_parsed = ft_split(command, data->operand);
	else
		command_parsed = ft_split(command, ' ');
	return (command_parsed);
}

static int	treat_space(t_data *data, char *command)
{
	int		is_space;
	int		i;

	is_space = 0;
	i = 0;
	if (ft_strnstr(command, "' ", ft_strlen(command)))
	{
		change_char(data, command);
		is_space = 1;
		while (command[i])
		{
			if (command[i] == SPACE)
				command[i] = data->operand;
			else if (command[i] == '\'' && command[i + 1] == SPACE)
			{
				command[i] = data->operand;
				i++;
				while (command[i] == SPACE)
					i++;
				command[i] = data->operand;
			}
			i++;
		}
	}
	return (is_space);
}

static void	change_char(t_data *data, char *command)
{
	if (ft_strnstr(command, ";", ft_strlen(command)))
		data->operand = HASH;
	else
		data->operand = SEMICOLON;
}
