/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-d <gcosta-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 21:06:34 by gcosta-d          #+#    #+#             */
/*   Updated: 2021/12/22 04:06:33 by gcosta-d         ###   ########.fr       */
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

# define VALID_PATHS "/usr/local/sbin/:/usr/local/bin/:/usr/sbin/:/usr/bin\
/:/sbin/:/bin/:/usr/games/:/usr/local/games/:/snap/bin"

typedef struct s_data {
	char	*file1;
	char	*file2;
	char	**arg1;
	char	**arg2;
	char	*cmd1;
	char	*cmd2;
	char	*file_path;
	int		file_ok;
	int		pipe_ok;
	int		pid_1;
	int		pid_2;
	int		fd[2];
	int		file_in;
	int		file_out;
}	t_data;

void	handle_errors(int signal, t_data *data);
void	pipex_in(t_data *data, char *envp[]);
void	pipex_out(t_data *data, char *envp[]);
void	free_exit(t_data *data);
char	*file_found(char *command);
void	ft_putendl_fd(char *s, int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t size);
char	*ft_strjoin(char *s1, char const *s2);
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t nbr, size_t size);

#endif
