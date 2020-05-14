# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lugibone <lugibone@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/02 15:19:01 by lugibone          #+#    #+#              #
#    Updated: 2019/11/06 17:01:20 by lugibone         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

RESET = \e[0m
BOLD = \e[1m
DIM	=	\e[2m
ITALIC = \e[3m
UNDERLINE = \e[4m
BLINK = \e[5m
REVERSED = \e[7m
HIDDEN = \e[8m
DEFAULT = \e[39m
BLACK = \e[30m
RED = \e[31m
GREEN = \e[32m
YELLOW = \e[33m
BLUE = \e[34m
MAGENTA = \e[35m
CYAN = \e[36m
LIGHT_GRAY = \e[37m
DARK_GRAY = \e[90m
WHITE = \e[97m
BG_DEFAULT = \e[49m
BG_BLACK = \e[30m
BG_RED = \e[41m
BG_GREEN = \e[42m
BG_YELLOW = \e[43m
BG_BLUE = \e[44m
BG_MAGENTA = \e[45m
BG_CYAN = \e[46m
LIGHT_GRAY = \e[47m
DARK_GRAY = \e[100m
BG_WHITE = \e[107m

CCC = gcc
FLAGS = -g -Wall -Werror -Wextra
MLX = minilibx/libmlx.a
MLX_PATH = ./minilibx
SRC_PATH = ./
OBJ_PATH = ./
OBJ_NAME = $(SRC_NAME:.c=.o)
SRC_NAME =	main.c			\
		keys_board.c	\
		keys_mouse.c	\
		parse.c			\
		update.c		\
		draw.c			\
		image.c			\
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
OBJS := $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
SRCS := $(addprefix $(SRC_PATH)/,$(SRC_NAME))
LIB_PATH = ./libft
LIBFT = ./libft/libft.a
INCLUDES = ./libft/includes

all:	$(NAME)

$(NAME): $(SRCS) $(LIBFT) $(MLX)
	@make -j objects
	@cc -lm -I $(INCLUDES) $(OBJS) -L libft -lft $(MLX) -lXext -lXext -lX11 -lm -o $(NAME)
	@printf "$(RESET)$(BOLD)$(BG_GREEN)$(WHITE)$(DIM) DONE $(RESET)\n"

objects: $(OBJS)

$(LIBFT):
	@make -C $(LIB_PATH)

$(MLX):
	@make -C minilibx

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@gcc $(FLAGS) -I $(INCLUDES) -c $< -o $@
	@printf "$(RESET)$(BG_GREEN) $(RESET)"

clean:
	@rm -rf $(OBJS)
	@make -C $(LIB_PATH) clean
	@make -C $(MLX_PATH) clean
	@printf "$(RESET)$(BG_CYAN)$(WHITE) PROJECT O_FILES CLEANED $(RESET)\n"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIB_PATH) fclean
	@printf "$(RESET)$(BG_CYAN)$(WHITE) EXEC: $(NAME) CLEANED $(RESET) \n"

re: fclean $(NAME)

.PHONY: all, clean, fclean, re
