# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/29 11:33:59 by amalecki          #+#    #+#              #
#    Updated: 2022/01/05 12:13:17 by amalecki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c ft_atoi.c basic_utils.c basic_utils2.c philosopher_threads.c death_checker_threads.c \
philosopher_threads_utils.c

CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread -lpthread # -fsanitize=thread

NAME = philo

RM = rm -rf

all: $(NAME)

$(NAME): $(SRC) philo.h
	$(CC) $(CFLAGS) $(SRC) -o $(NAME) 

clean:

fclean:
	$(RM) $(NAME)

re:     fclean all

.PHONY:         all clean fclean re
