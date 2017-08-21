# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sasha <sasha@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/21 11:27:39 by sasha             #+#    #+#              #
#    Updated: 2017/08/21 11:28:01 by sasha            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	ft_retro

CFLAGS	=	-Wall -Wextra -Werror
CC		=	clang++

SRC		=	Map.cpp \
			Entity.cpp \
			Game.cpp \
			main.cpp

all: $(NAME)

$(NAME):
	$(CC) $(FLAGS) -o $(NAME) $(SRC) -lncurses

fclean:
	rm -f $(NAME)

re: fclean all
