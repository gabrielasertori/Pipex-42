/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-d <gcosta-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 21:06:34 by gcosta-d          #+#    #+#             */
/*   Updated: 2021/12/22 00:41:43 by gcosta-d         ###   ########.fr       */
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
	char	*limiter;
	char	*file_path;
	char	**cmds;
	char	***args;
	int		file_ok;
	int		here_doc;
	int		pipe_ok;
	int		*pids;
	int		cmds_list;
	int		fd[2];
	int		file_in;
	int		file_out;
}	t_data;

void	ft_putendl_fd(char *s, int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t size);
char	*ft_strjoin(char *s1, char const *s2);
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t nbr, size_t size);
void	handle_here_doc(char *argv[], t_data *data);
void	handle_errors(int signal, t_data *data);
char	*file_found(char *command);
int		fork_ncommands(int count, t_data *data, char *envp[]);
void	free_exit(t_data *data);
void	free_matrix(t_data *data);

#endif