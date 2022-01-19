/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-d <gcosta-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:37:24 by gcosta-d          #+#    #+#             */
/*   Updated: 2022/01/19 18:03:45 by gcosta-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/pipex_bonus.h"

void	here_doc(t_data *data)
{
	char	*line;

	line = get_next_line(STDIN_FILENO);
	while (1)
	{
		if (ft_strnstr(line, data->limiter, ft_strlen(data->limiter)))
			break ;
		write(data->file_in, line, ft_strlen(line));
		line = get_next_line(STDIN_FILENO);
	}
}
