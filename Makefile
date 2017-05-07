# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbrochar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/10 02:28:41 by gbrochar          #+#    #+#              #
#    Updated: 2016/06/22 04:27:12 by gbrochar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

SRC =	main.c \
		event_hook.c \
		parsing.c \
		parsing_2.c \
		pixel_put.c \
		run_game.c

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Werror -Wextra -g3

all: $(NAME)

$(NAME):
	make -C libft
	gcc $(FLAGS) -c $(SRC)
	gcc $(OBJ) -o $(NAME) libft/libft.a -lm \
	-lmlx -framework Appkit -framework OpenGL

clean:
	make -C libft clean
	rm -f $(OBJ)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)
	rm -rf wolf3d.dSYM

re: fclean all
