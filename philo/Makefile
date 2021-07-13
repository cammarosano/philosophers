# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/11 19:04:56 by rcammaro          #+#    #+#              #
#    Updated: 2021/07/13 18:34:01 by rcammaro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c setup.c philo_actions.c clear_mem.c time.c checks.c parse.c
HEADER = philo.h
OBJ = $(SRC:.c=.o)
NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread

all:	$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) $^ -o $@

%.o:		%.c $(HEADER)
			$(CC) $(CFLAGS) -c $< -o $@

clean:
			rm -rf $(OBJ)

fclean:		clean
			rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re