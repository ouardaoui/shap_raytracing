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
CFLAGS =  -Wall -Werror -Wextra -fsanitize=adddress  -Ofast
LIBMLX = ../os/libmlx42.a
SRCS = src/main.c \
	src/parse.c \
	src/parse_elem.c \
	src/math_tools.c  \
	src/parsing_tools.c \
	src/list_tools.c \
	src/list_tools_two.c \
	src/get_next_line.c \
	src/render.c \
	src/shading_tools.c	\
	src/math_tools_two.c  \
	src/drew.c \
	src/normal_handle.c \
	src/inter_objects.c \
	src/tools.c \
	src/inter_cylindre.c
NAME = miniRT

all: $(NAME)

$(NAME): $(SRCS)
	@$(CC) $(FLAGS) $(SRCS) $(LIBMLX) utils/libft.a  -lglfw -L"/goinfre/aouardao/brew/Cellar/glfw/3.3.8/lib" -o $(NAME)

run:
	make re && ./miniRT

clean:
	@rm -rf $(NAME)

fclean: clean


re: fclean all

.PHONY:	all bonus clean fclean re

