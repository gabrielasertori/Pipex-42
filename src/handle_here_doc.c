/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-d <gcosta-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 21:36:53 by gcosta-d          #+#    #+#             */
/*   Updated: 2021/12/16 00:39:10 by gcosta-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	handle_here_doc(char *argv[], t_data *data)
{
	data->file1 = argv[2];
	data->file_ok = access(data->file1, F_OK);

	if (data->file_ok == -1)
		handle_errors(1);
}