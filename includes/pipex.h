/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-d <gcosta-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 21:06:34 by gcosta-d          #+#    #+#             */
/*   Updated: 2022/02/10 03:34:08 by gcosta-d         ###   ########.fr       */
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
# include <errno.h>
# include <stdio.h>

# define VALID_PATHS "/usr/local/sbin/:/usr/local/bin/:/usr/sbin/:/usr/bin\
/:/sbin/:/bin/:/usr/games/:/usr/local/games/:/snap/bin/"
# define MAX_FD 256
# define BUFFER_SIZE 1
# define SPACE ' '
# define SEMICOLON ';'
# define HASH '#'

typedef struct s_data {
	char	*file_path;
	char	*file1;
	char	*file2;
	char	operand;
	int		fd[2];
	int		file_in;
	int		file_out;
	pid_t	pid;
}	t_data;

// ===== MAIN FUNCTIONS =====
void	handle_errors(int signal);
void	pipex(t_data *data, char *argv[], char *envp[]);
void	init_args(int argc, char *argv[], t_data *data);
void	free_matrix(char **matrix);
char	*command_finder(char *command);
char	**parse_argv(t_data *data, char *command);

// ===== LIBFT FUNCTIONS =====
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char *s, char c);
char	*ft_strnstr(const char *s1, const char *s2, size_t	n);
void	*ft_calloc(size_t nbr, size_t size);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);

#endif
