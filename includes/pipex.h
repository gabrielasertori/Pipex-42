/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-d <gcosta-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 21:06:34 by gcosta-d          #+#    #+#             */
/*   Updated: 2021/12/16 15:35:27 by gcosta-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>

# include <stdio.h>

typedef struct s_data {
	char	*file1;
	char	*file2;
	char	**arg1;
	char	**arg2;
	int		file_ok;
	int		pipe_ok;
	int		pid_1;
	int		pid_2;
	int		fd[2];
	int		file_in;
	int		file_out;
}	t_data;

void	ft_putendl_fd(char *s, int fd);
void	handle_here_doc(char *argv[], t_data *data);
int		ft_strncmp(const char *s1, const char *s2, size_t size);
void	handle_errors(int signal);

#endif