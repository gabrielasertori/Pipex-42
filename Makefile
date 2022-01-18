# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gcosta-d <gcosta-d@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/15 21:06:19 by gcosta-d          #+#    #+#              #
#    Updated: 2022/01/18 19:13:26 by gcosta-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ./pipex
SRC_PATH = ./src/
SRC = $(SRC_PATH)pipex_utils.c \
	$(SRC_PATH)pipex.c \
	$(SRC_PATH)handle_errors.c \
	$(SRC_PATH)pipex_utils_2.c \
	$(SRC_PATH)treat_space.c
OBJ_PATH = ./objs/
OBJ = $(subst $(SRC_PATH),$(OBJ_PATH),$(SRC:%.c=%.o))
CFLAGS = -Wall -Wextra -Werror -g
SUCCESS = @echo "\033[36m-----------\033[0m" && \
	echo "\033[36m| SUCCESS |\033[0m" && \
	echo "\033[36m-----------\033[0m"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	mkdir -p objs
	gcc $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(CFLAGS) -o $(NAME) ./src/main.c $(OBJ) -I./includes
	$(SUCCESS)

clean:
	rm -f $(OBJ)
	$(SUCCESS)

fclean: clean
	rm -rf $(OBJ_PATH)
	rm -f $(NAME)
	$(SUCCESS)

re: fclean all

#------- BONUS -------
NAME_BONUS = ./pipex_bonus
SRC_PATH_BONUS = ./src_bonus/
SRC_BONUS = $(SRC_PATH_BONUS)pipex_utils_bonus.c \
	$(SRC_PATH_BONUS)pipex_bonus.c \
	$(SRC_PATH_BONUS)handle_errors_bonus.c \
	$(SRC_PATH_BONUS)pipex_utils_bonus_2.c \
	$(SRC_PATH_BONUS)treat_space_bonus.c \
	$(SRC_PATH_BONUS)init_bonus.c \
	$(SRC_PATH_BONUS)here_doc.c \
	$(SRC_PATH_BONUS)command_finder.c
OBJ_PATH_BONUS = ./objs_bonus/
OBJ_BONUS = $(subst $(SRC_PATH_BONUS),$(OBJ_PATH_BONUS),$(SRC_BONUS:%.c=%.o))

$(OBJ_PATH_BONUS)%.o: $(SRC_PATH_BONUS)%.c
	mkdir -p objs_bonus
	gcc $(CFLAGS) -c $< -o $@

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJ_BONUS)
	gcc $(CFLAGS) -o $(NAME_BONUS) ./src_bonus/main_bonus.c $(OBJ_BONUS) -I./includes_bonus
	$(SUCCESS)

b_clean:
	rm -f $(OBJ_BONUS)
	$(SUCCESS)

b_fclean: b_clean
	rm -rf $(OBJ_PATH_BONUS)
	rm -f $(NAME_BONUS)
	$(SUCCESS)

b_re: b_fclean bonus
