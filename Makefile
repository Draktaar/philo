# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: achu <achu@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/22 21:33:14 by achu              #+#    #+#              #
#    Updated: 2025/04/23 02:13:34 by achu             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		philo
CC =		cc
CFLAGS =	-Wall -Wextra

SRC =		src/main.c \
			src/routine.c \

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) -c $< -o $@

$(OBJS):

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re