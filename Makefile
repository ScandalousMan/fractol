# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aguemy <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/15 14:04:04 by aguemy            #+#    #+#              #
#    Updated: 2017/05/08 15:39:31 by aguemy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
CC = gcc
CFLAGS =  -Wall -Werror -Wextra
LFLAGS = -lmlx -framework AppKit -framework OpenGL -L $(LIB_PATH) -lft
HEADER = -I./include
OBJ = $(SRC:.c=.o)
LIB_PATH = ./libft/
LIB = $(LIB_PATH)libft.a
SRC = main.c \
	starters.c \
	starters2.c \
	iterations.c \
	components.c \
	ft_atod.c \
	key_func.c \
	mouse_func.c \
	algorithms.c \
	buddhabrot_components2.c \
	buddhabrot_components.c

# COLORS
C_NO = "\033[00m"
C_OK = "\033[34m"
C_GOOD = "\033[32m"
C_ERROR = "\033[31m"
C_WARN = "\033[33m"

# DBG MESSAGE
SUCCESS = [ $(C_GOOD)OK$(C_NO) ]
OK = [ $(C_OK)OK$(C_NO) ]

all: $(LIB) $(NAME)

$(LIB):
	@make -C $(LIB_PATH)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $@ $(OBJ) $(LFLAGS) $(HEADER)
	@echo $(SUCCESS)" Compiling" $(NAME) "\t\t"

%.o: %.c ./include/fractol.h
	@$(CC) $(CFLAGS) $(HEADER) -c -o $@ $<
	@echo $(OK)" Linking $< \t\t"

clean:
	@rm -f $(OBJ)
	@make -C $(LIB_PATH) clean
	@echo $(OK)" Cleaning $(NAME) \t\t"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIB_PATH) fclean
	@echo $(OK)" Delete $(NAME) \t\t"

re: fclean all

.PHONY: all clean fclean re $(LIB)
