# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iharile <iharile@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/27 19:48:42 by iharile           #+#    #+#              #
#    Updated: 2022/08/30 13:31:54 by iharile          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
#SANITIZE = -fsanitize=thread
THREAD = -lpthread
FILES = main.c routine.c utils.c 
OBJET = $(FILES:.c=.o)

all: $(NAME)

$(NAME) : $(OBJET)
	$(CC) $(CFLAGS) $(SANITIZE)  $(THREAD) $(OBJET) -o $(NAME)
clean :
	rm -rf $(OBJET)

fclean : clean
	rm -rf $(NAME)

re : fclean all