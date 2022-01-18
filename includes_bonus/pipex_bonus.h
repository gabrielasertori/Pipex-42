/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-d <gcosta-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 21:06:34 by gcosta-d          #+#    #+#             */
/*   Updated: 2022/01/18 21:56:59 by gcosta-d         ###   ########.fr       */
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
/:/sbin/:/bin/:/usr/games/:/usr/local/games/:/snap/bin/"
# define MAX_FD 256
# define BUFFER_SIZE 1

typedef struct s_data {
	char	*file_path;
	char	*file1;
	char	*file2;
	char	*limiter;
	int		heredoc;
	int		qnt_cmds;
	int		file_ok;
	int		fd[2];
	int		file_in;
	int		file_out;
	pid_t	pid;
}	t_data;

// ===== MAIN FUNCTIONS =====
void	handle_errors(int signal, t_data *data);
void	pipex(t_data *data, char *argv[], char *envp[]);
void	free_matrix(char **matrix);
void	init_args(int argc, char *argv[], t_data *data);
void	here_doc(t_data *data);
char	*command_finder(char *command);
char	**parse_argv(t_data *data, char *command);
// ===== LIBFT FUNCTIONS =====
char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char *s, char c);
size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t nbr, size_t size);
char	*ft_strnstr(const char *s1, const char *s2, size_t	n);

#endif
