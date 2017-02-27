# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aguemy <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/15 14:04:04 by aguemy            #+#    #+#              #
#    Updated: 2017/02/27 20:56:41 by aguemy           ###   ########.fr        #
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
	components.c \
	key_func.c \
	mandelbrot.c \
	julia.c

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
