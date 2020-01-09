# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/06 12:52:28 by mribouch          #+#    #+#              #
#    Updated: 2020/01/09 15:11:14 by mribouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

SRCS = main.c			\
		keys_board.c	\
		keys_mouse.c	\
		parse.c			\
		update.c		\
		draw.c			\
		draw_tools.c	\
		action.c		\
		action_tools.c	\
		tools.c			\
		menu.c			\
		menu_button.c	\
		shape.c			\
		map.c			\
		color.c			\
		load.c			\
		tnt.c			\
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