# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/29 11:33:59 by amalecki          #+#    #+#              #
#    Updated: 2022/01/07 11:40:34 by amalecki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main_bonus.c ft_atoi.c basic_utils.c fork_utils.c philo_cycle_utils.c \
philo_cycle_utils2.c

CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread -lpthread # -fsanitize=thread

NAME = philo_bonus

RM = rm -rf

all: $(NAME)

$(NAME): $(SRC) philo_bonus.h
	$(CC) $(CFLAGS) $(SRC) -o $(NAME) 

clean:

fclean:
	$(RM) $(NAME)

re:     fclean all

.PHONY:         all clean fclean re
