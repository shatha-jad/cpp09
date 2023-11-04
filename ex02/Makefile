# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkhan <mkhan@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/19 13:21:45 by mkhan             #+#    #+#              #
#    Updated: 2023/07/09 14:20:21 by mkhan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	main.cpp PmergeMe.cpp

OBJ =	$(SRC:.cpp=.o)

CC =	c++

RM =	rm -f

CFLAGS = -Wall -Wextra -Werror -std=c++98 -g3

NAME =	PmergeMe

%.o : %.cpp
			$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $@

clean:
	@$(RM) $(OBJ)

fclean: clean
		@$(RM) $(NAME) 

re: fclean all

.PHONY: all clean fclean re