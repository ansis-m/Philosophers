# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/29 11:33:59 by amalecki          #+#    #+#              #
#    Updated: 2021/12/31 16:24:50 by amalecki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c ft_atoi.c basic_utils.c

CC = cc

CFLAGS = -Wall -Wextra -lpthread #-Werror #-pthread  proly not needed

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
