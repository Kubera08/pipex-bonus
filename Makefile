# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abeaudui <abeaudui@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/21 13:06:31 by arnaud            #+#    #+#              #
#    Updated: 2023/03/08 15:56:57 by abeaudui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = pipex

FLAGS = -Wall -Wextra -Werror

SRC = pipex.c utils.c  split.c path.c free.c

OBJS = $(SRC:.c=.o)

CC = gcc

RM = rm -rf

INC =  include

.c.o:
	$(CC) $(FLAGS) -I $(INC) -c $< -o $(<:.c=.o)

all: $(NAME)

$(NAME):	$(OBJS)
	$(CC) $(FLAGS) -I $(INC) -o $(NAME) $(OBJS) 

clean:

	$(RM) $(OBJS) $(NAME) 


fclean: clean
	$(RM) 
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re