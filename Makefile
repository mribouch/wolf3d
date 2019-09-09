# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/06 12:52:28 by mribouch          #+#    #+#              #
#    Updated: 2019/08/14 16:16:29 by mribouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

SRCS = main.c		\
		keys.c		\
		parse.c		\
		bresenham.c	\
		shape.c		\
		ray.c		\
		draw.c		\
		init.c

FLAGS = -Wall -Wextra -Werror
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