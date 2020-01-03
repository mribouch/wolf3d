# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/06 12:52:28 by mribouch          #+#    #+#              #
#    Updated: 2019/11/21 14:13:29 by mribouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

SRCS = main.c			\
		keys.c			\
		parse.c			\
		update.c		\
		draw.c			\
		action.c		\
		tools.c			\
		menu.c			\
		menu_button.c	\
		shape.c			\
		map.c			\
		color.c			\
		edit.c			\
		free.c			\
		init.c

FLAGS = -Wall -Wextra -Werror -g3
OBJS = $(SRCS:.c=.o)

LIBFT = libft/libft.a
MLX = minilibx_macos/libmlx.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX) wolf.h
	gcc $(FLAGS) $(MLX) $(LIBFT) $(OBJS) \
	-framework OpenGL -framework Appkit -o wolf3d

%.o: %.c
	gcc $(FLAGS) -c $< -o $@

$(LIBFT):
	make -C libft

$(MLX):
	make -C minilibx_macos

clean:
	rm -rf $(OBJS)
	make clean -C libft/

fclean: clean
	rm -rf wolf3d libft/libft.a minilibx_macos/libmlx.a

re: fclean $(NAME)