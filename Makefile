# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmelehov <dmelehov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/22 14:02:51 by dmelehov          #+#    #+#              #
#    Updated: 2017/10/27 13:29:30 by dmelehov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d
LIBFT = libft/libft.a
LIBS = $(LIBFT) -L./ -lmlx
HPATH = -I./
SRC = main.c fill_struct.c my_keys.c raycasting.c
CC = gcc -g -Wall -Wextra -Werror
C_MLX = -framework OpenGL -framework AppKit
AR = ar - cvq libft.a
RM = rm -rf
SRCDIR = $(addprefix ./src/, $(SRC))
OBJDIR = obj
OBJ = $(addprefix ./$(OBJDIR)/, $(SRC:.c=.o))

$(NAME):
	@make -C libft
	@$(CC) -c $(SRC)
	@mkdir -p $(OBJDIR) && mv $(SRC:.c=.o) ./$(OBJDIR)/
	@$(CC) -o $(NAME) $(OBJ) $(LIBS) $(C_MLX) $(HPATH)

all: $(NAME)

clean:
	@$(RM) $(OBJDIR)
	@make clean -C libft

fclean: clean
	@make fclean -C libft
	@$(RM) $(NAME)

re: fclean
	@make re -C libft
	@make all
#@make clean

.PHONY: all clean fclean