# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aouardao <aouardao@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/08 17:11:01 by hahadiou          #+#    #+#              #
#    Updated: 2023/08/17 07:13:25y aouardao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= cc
CFLAGS = -Wall -Werror -Wextra
LIBMLX = ../unix/libmlx42.a
SRCS = src/main.c \
	src/parse.c \
	src/parse_elem.c \
	src/math_tools.c  \
	src/parsing_tools.c \
	src/list_tools.c \
	src/get_next_line.c \
	src/render.c
		
NAME = miniRT

all: $(NAME)

$(NAME): $(SRCS)
	@$(CC) $(FLAGS) $(SRCS) $(LIBMLX) src/libft.a -lglfw -lm -o $(NAME)

run:
	make re && ./miniRT

clean:
	@rm -rf $(NAME)

fclean: clean


re: fclean all

.PHONY:	all bonus clean fclean re

