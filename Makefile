# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: achu <achu@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/22 21:33:14 by achu              #+#    #+#              #
#    Updated: 2025/04/24 02:08:19 by achu             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		philo
CC =		cc
CFLAGS =	-Wall -Wextra

INC =		inc
SRC =		src/init.c \
			src/routine.c \
			src/status.c \
			src/free.c \
			src/utils.c \
			src/main.c

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -I $(INC) -o $(NAME)

%.o: %.c
	$(CC) -I $(INC) -c $< -o $@

$(OBJS):

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re