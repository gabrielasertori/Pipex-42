/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-d <gcosta-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 21:24:01 by gcosta-d          #+#    #+#             */
/*   Updated: 2022/02/17 23:29:02 by gcosta-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/pipex_bonus.h"

static void		treat_space(t_data *data, char *command);
static size_t	strchr_qnt(char *command, char c);
static int		strichar(char *command, int pos, char c);
static char		*change_bytes(char *command, int start, int end, char c);

void	parse_argv(t_data *data, char *command)
{
	if (strchr_qnt(command, SINGLE_QUOTE) > 1)
		treat_space(data, command);
	else
		data->cmd_parsed = ft_split(command, SPACE);
}

static void	treat_space(t_data *data, char *command)
{
	char	*cmd_changed;
	char	*substr;
	int		first_char;
	int		sec_char;
	int		i;

	first_char = strichar(command, 0, SINGLE_QUOTE);
	sec_char = strichar(command, first_char + 1, SINGLE_QUOTE);
	substr = ft_substr(command, first_char + 1, sec_char - first_char - 1);
	cmd_changed = change_bytes(command, first_char, sec_char, PERCENT);
	data->cmd_parsed = ft_split(cmd_changed, SPACE);
	free(cmd_changed);
	i = -1;
	while (data->cmd_parsed[++i])
	{
		if (strchr_qnt(data->cmd_parsed[i], PERCENT) == \
			ft_strlen(data->cmd_parsed[i]))
		{
			free(data->cmd_parsed[i]);
			data->cmd_parsed[i] = ft_strdup(substr);
			free(substr);
		}
	}
}

static size_t	strchr_qnt(char *command, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (command[i])
	{
		if (command[i] == c)
			j++;
		i++;
	}
	return (j);
}

static int	strichar(char *command, int pos, char c)
{
	while (command[pos] != c)
		pos++;
	return (pos);
}

static char	*change_bytes(char *command, int start, int end, char c)
{
	char	*cmd;

	cmd = ft_strdup(command);
	while (start <= end)
	{
		cmd[start] = c;
		start++;
	}
	return (cmd);
}
