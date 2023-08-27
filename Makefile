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
FLAGS	=   -IINC -fsanitize=address -g -Wunreachable-code -Ofast
UNAME_S := $(shell uname -s)
LIBMLX = ../os/libmlx42.a
LIB_PATH =  -Iinclude -lglfw -L"/goinfre/aouardao/brew/Cellar/glfw/3.3.8/lib"
##ifeq ($(UNAME_S),Linux)
##LIB_PATH =  -Iinclude -ldl -lglfw -pthread -lm
##LIBMLX = ../unix/libmlx42.a
##endif
NAME	= miniRT

INC	= include
SRC_PATH	= src
UTILS_PATH	= utils
OBJ_PATH	= obj

SRCS = main.c \
						parse.c \
						parse_elem.c \
						math_tools.c  \
						parsing_tools.c \
						list_tools.c \
						get_next_line.c
		
SRC		= $(addprefix $(SRC_PATH)/,$(SRCS))
OBJ		= $(addprefix $(OBJ_PATH)/,$(SRCS:.c=.o))

NOC		= \033[0m
RED		= \033[1;31m
GREEN	= \033[1;32m
YELLOW	= \033[1;33m
BLUE	= \033[1;34m
WHITE	= \033[1;37m

all: $(NAME)

bonus: $(NAMEB)

$(NAME): $(OBJ)
	@echo "$(YELLOW)Compiling Utils...$(NOC)"
	@echo "$(YELLOW)Compiling miniRT...$(NOC)"
	@$(CC) $(FLAGS) $(LIBMLX) $(LIB_PATH) -o $@ $^
	@echo "$(GREEN)$@$(NOC)"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INC)/minirt.h
	@mkdir -p obj
	@$(CC) $(FLAGS) -I$(INC) -c -o $<  src/libft.a

run:
	make re && ./miniRT
clean:
	@echo "$(RED)Deleting OBJS ✔️ $(NOC)"
	@make clean -sC $(UTILS_PATH)
	@rm -rf $(OBJ_PATH)

fclean: clean
	@echo "$(RED)Deleting Binary ✔️$(NOC)"
	@make fclean -sC $(UTILS_PATH)
	@rm -f $(NAME)

re: fclean all

.PHONY:	all bonus clean fclean re

