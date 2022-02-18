/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-d <gcosta-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:55:00 by gcosta-d          #+#    #+#             */
/*   Updated: 2022/02/18 00:09:23 by gcosta-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/pipex_bonus.h"

static char	*get_line(int fd, char **buffer, char *read_buffer);
static char	*format_line(char **buffer, char *swap, int new_line_index);
static void	ft_free(char **ptr);

static void	ft_free(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

static char	*format_line(char **buffer, char *swap, int new_line_index)
{
	char	*line_formated;

	if (new_line_index < 0)
	{
		if (!**buffer && !swap)
		{
			free(*buffer);
			*buffer = NULL;
			return (NULL);
		}
		line_formated = ft_strdup(*buffer);
		free(*buffer);
		*buffer = NULL;
		return (line_formated);
	}
	*buffer = ft_substr(swap, new_line_index + 1, ft_strlen(swap));
	swap[new_line_index + 1] = '\0';
	line_formated = swap;
	return (line_formated);
}

static char	*get_line(int fd, char **buffer, char *read_buffer)
{
	int		read_bytes;
	char	*swap;
	char	*find_new_line;
	int		new_line_position;

	swap = NULL;
	find_new_line = ft_strchr(*buffer, '\n');
	while (find_new_line == NULL)
	{
		read_bytes = read(fd, read_buffer, BUFFER_SIZE);
		if (read_bytes <= 0)
			return (format_line(buffer, swap, -1));
		read_buffer[read_bytes] = '\0';
		swap = ft_strjoin(*buffer, read_buffer);
		ft_free(buffer);
		*buffer = swap;
		find_new_line = ft_strchr(*buffer, '\n');
	}
	swap = *buffer;
	new_line_position = 0;
	while (swap[new_line_position] != '\n')
		new_line_position++;
	return (format_line(buffer, swap, new_line_position));
}

char	*get_next_line(int fd)
{
	static char	*buffer[MAX_FD];
	char		*read_buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > MAX_FD)
		return (NULL);
	if (!buffer[fd])
		buffer[fd] = ft_strdup("");
	read_buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!read_buffer)
		return (NULL);
	line = get_line(fd, &buffer[fd], read_buffer);
	ft_free(&read_buffer);
	ft_free(buffer);
	return (line);
}
