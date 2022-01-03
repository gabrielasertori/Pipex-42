/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-d <gcosta-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 21:06:34 by gcosta-d          #+#    #+#             */
/*   Updated: 2022/01/03 22:59:33 by gcosta-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>

# include <stdio.h>

# define VALID_PATHS "/usr/local/sbin/:/usr/local/bin/:/usr/sbin/:/usr/bin\
/:/sbin/:/bin/:/usr/games/:/usr/local/games/:/snap/bin"

typedef struct s_data {
	char	***args;
	char	**cmds;
	char	**file_path;
	char	*file1;
	char	*file2;
	char	*limiter;
	int		qnt_cmds;
	int		file_ok;
	int		pipe_ok;
	int		pid;
	int		fd[2];
	int		file_in;
	int		file_out;
}	t_data;

void	handle_errors(int signal, t_data *data);
void	pipex(t_data *data, char *envp[], int i);
void	free_matrix(char **matrix);
void	free_exit(t_data *data);
char	*file_found(char *command);
int		treat_space(char *command);
void	init_args(int argc, char *argv[], t_data *data);
void	init_hdoc_args(char *argv[], t_data *data);
void	init_multi_args(int argc, char *argv[], t_data *data);
void	ft_putendl_fd(char *s, int fd);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char *s, char c);
size_t	ft_strlcpy(char *dest, char *src, size_t size);
size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t nbr, size_t size);
char	*ft_strnstr(const char *s1, const char *s2, size_t	n);

#endif
