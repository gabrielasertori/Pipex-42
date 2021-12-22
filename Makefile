# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gcosta-d <gcosta-d@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/15 21:06:19 by gcosta-d          #+#    #+#              #
#    Updated: 2021/12/22 03:57:03 by gcosta-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ./pipex
SRC_PATH = ./src/
SRC = $(SRC_PATH)pipex_utils.c \
	$(SRC_PATH)pipex.c \
	$(SRC_PATH)handle_errors.c \
	$(SRC_PATH)pipex_utils_2.c
OBJ_PATH = ./objs/
OBJ = $(subst $(SRC_PATH),$(OBJ_PATH),$(SRC:%.c=%.o))
CFLAGS = -Wall -Wextra -Werror
SUCCESS = @echo "\033[36m-----------\033[0m" && \
	echo "\033[36m| SUCCESS |\033[0m" && \
	echo "\033[36m-----------\033[0m"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	mkdir -p objs
	gcc $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) ./src/main.c $(OBJ) -I./includes
	$(SUCCESS)

clean:
	rm -f $(OBJ)
	$(SUCCESS)

fclean: clean
	rm -rf $(OBJ_PATH)
	rm -f $(NAME)
	$(SUCCESS)

re: fclean all
