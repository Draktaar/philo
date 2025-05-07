# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: achu <achu@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/22 21:33:14 by achu              #+#    #+#              #
#    Updated: 2025/05/05 16:45:57 by achu             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		philo
CC =		cc
CFLAGS =	-Wall -Wextra

INC =		inc
SRC =		src/init.c \
			src/philo.c \
			src/status.c \
			src/clean.c \
			src/utils.c \
			src/main.c

OBJS = $(SRC:.c=.o)

HEADERS = inc/philo.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -I $(INC) -o $(NAME)

%.o: %.c
	$(CC) -I $(INC) -c $< -o $@

$(OBJS): $(HEADERS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
