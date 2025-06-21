# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/26 02:35:14 by hmoukit           #+#    #+#              #
#    Updated: 2025/06/20 21:01:00 by hmoukit          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = server

SRCS = main.cpp miniServer.cpp

OBJS = $(SRCS:.cpp=.o)

CPP = c++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98

all: $(NAME)

$(NAME): $(OBJS)
	$(CPP) $(CPPFLAGS) $(OBJS) -o $(NAME)
	
%.o: %.cpp miniServer.hpp
	$(CPP) $(CPPFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re