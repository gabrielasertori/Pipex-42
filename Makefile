# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gcosta-d <gcosta-d@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/15 21:06:19 by gcosta-d          #+#    #+#              #
#    Updated: 2022/02/17 04:13:41 by gcosta-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ./pipex

SRC_PATH = ./src/
SRC = $(SRC_PATH)pipex.c \
	$(SRC_PATH)parse_argv.c \
	$(SRC_PATH)init.c \
	$(SRC_PATH)command_finder.c \
	$(SRC_PATH)handle_errors.c

UTILS_PATH = ./utils/
UTILS = $(UTILS_PATH)ft_split.c \
		$(UTILS_PATH)ft_strchr.c \
		$(UTILS_PATH)ft_strdup.c \
		$(UTILS_PATH)ft_strjoin.c \
		$(UTILS_PATH)ft_strlen.c \
		$(UTILS_PATH)ft_strnstr.c \
		$(UTILS_PATH)ft_calloc.c \
		$(UTILS_PATH)ft_strlcpy.c \
		$(UTILS_PATH)ft_substr.c

OBJ_PATH = ./objs/
OBJ = $(subst $(SRC_PATH),$(OBJ_PATH),$(SRC:%.c=%.o))

OBJ_PATH_UTILS = ./objs_utils/
OBJ_UTILS = $(subst $(UTILS_PATH),$(OBJ_PATH_UTILS),$(UTILS:%.c=%.o))

CFLAGS = -Wall -Wextra -Werror -g3
SUCCESS = @echo "\033[36m-----------\033[0m" && \
	echo "\033[36m| SUCCESS |\033[0m" && \
	echo "\033[36m-----------\033[0m"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	mkdir -p objs
	gcc $(CFLAGS) -c $< -o $@

$(OBJ_PATH_UTILS)%.o: $(UTILS_PATH)%.c
	mkdir -p objs_utils
	gcc $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ) $(OBJ_UTILS)
	gcc $(CFLAGS) -o $(NAME) ./src/main.c $(OBJ) $(OBJ_UTILS) -I./includes
	$(SUCCESS)

clean:
	rm -f $(OBJ)
	rm -f $(OBJ_UTILS)
	$(SUCCESS)

fclean: clean
	rm -rf $(OBJ_PATH)
	rm -rf $(OBJ_PATH_UTILS)
	rm -f $(NAME)
	$(SUCCESS)

re: fclean all

#------- BONUS -------
NAME_BONUS = ./pipex_bonus

SRC_PATH_BONUS = ./src_bonus/
SRC_BONUS = $(SRC_PATH_BONUS)pipex_bonus.c \
	$(SRC_PATH_BONUS)handle_errors_bonus.c \
	$(SRC_PATH_BONUS)init_bonus.c \
	$(SRC_PATH_BONUS)here_doc_bonus.c \
	$(SRC_PATH_BONUS)command_finder_bonus.c \
	$(SRC_PATH_BONUS)parse_argv_bonus.c

UTILS_PATH_BONUS = ./utils_bonus/
UTILS_BONUS = $(UTILS_PATH_BONUS)ft_calloc.c \
	$(UTILS_PATH_BONUS)ft_split.c \
	$(UTILS_PATH_BONUS)ft_strchr.c \
	$(UTILS_PATH_BONUS)ft_strdup.c \
	$(UTILS_PATH_BONUS)ft_strjoin.c \
	$(UTILS_PATH_BONUS)ft_strlen.c \
	$(UTILS_PATH_BONUS)ft_substr.c \
	$(UTILS_PATH_BONUS)ft_strnstr.c \
	$(UTILS_PATH_BONUS)ft_strncmp.c \
	$(UTILS_PATH_BONUS)ft_strlcpy.c \
	$(UTILS_PATH_BONUS)gnl.c

OBJ_PATH_BONUS = ./objs_bonus/
OBJ_SRC_BONUS = $(subst $(SRC_PATH_BONUS),$(OBJ_PATH_BONUS),$(SRC_BONUS:%.c=%.o))

OBJ_UTILS_PATH_BONUS = ./objs_utils_bonus/
OBJ_UTILS_BONUS = $(subst $(UTILS_PATH_BONUS),$(OBJ_UTILS_PATH_BONUS),$(UTILS_BONUS:%.c=%.o))


$(OBJ_PATH_BONUS)%.o: $(SRC_PATH_BONUS)%.c
	mkdir -p objs_bonus
	gcc $(CFLAGS) -c $< -o $@

$(OBJ_UTILS_PATH_BONUS)%.o: $(UTILS_PATH_BONUS)%.c
	mkdir -p objs_utils_bonus
	gcc $(CFLAGS) -c $< -o $@

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJ_SRC_BONUS) $(OBJ_UTILS_BONUS)
	gcc $(CFLAGS) -o $(NAME_BONUS) ./src_bonus/main_bonus.c $(OBJ_SRC_BONUS) $(OBJ_UTILS_BONUS) -I./includes_bonus -fsanitize=address
	$(SUCCESS)

b_clean:
	rm -f $(OBJ_SRC_BONUS)
	rm -f $(OBJ_UTILS_BONUS)
	$(SUCCESS)

b_fclean: b_clean
	rm -rf $(OBJ_PATH_BONUS)
	rm -rf $(OBJ_UTILS_PATH_BONUS)
	rm -f $(NAME_BONUS)
	$(SUCCESS)

b_re: b_fclean bonus
