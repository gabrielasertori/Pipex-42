/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-d <gcosta-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 16:31:56 by gcosta-d          #+#    #+#             */
/*   Updated: 2021/12/22 18:29:18 by gcosta-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	treat_space(char *command)
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
			else if (command[i] == '\'')
			{
				i++;
				while (command[i] == ' ')
				{
					i++;
				}
			}
			i++;
		}
	}
	return (is_space);
}

// "tr;/;' '"
// "tr;' ';/"