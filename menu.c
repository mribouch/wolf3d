/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 14:49:28 by mribouch          #+#    #+#             */
/*   Updated: 2020/01/13 19:37:21 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	ft_act_button(t_window *infos, int id)
{
	if (id == 0)
	{
		infos->wolf.menu = 0;
		infos->map_menu = 0;
	}
	if (id == 1)
		infos->map_menu = 1;
	if (id == 2)
	{
		infos->edit_button[0].x = WIDTH / 2 - infos->edit_button[0].button_up.w;
		infos->edit_button[1].x = WIDTH / 2 + 50;
		infos->edit_button[0].y = HEIGHT / 2;
		infos->edit_button[1].y = HEIGHT / 2;
		infos->edit_button[0].press = 0;
		infos->edit_button[1].press = 0;
		infos->edit_menu = 1;
		infos->wolf.menu = 0;
		infos->map_menu = 0;
	}
	if (id == 3)
	{
		ft_quit_wolf(infos);
		exit(0);
	}
}

static int	ft_manage_button(t_window *infos, int x, int y, int id)
{
	int	w;
	int	h;

	w = infos->button[0].button_up.w;
	h = infos->button[0].button_up.h;
	if (infos->wolf.menu == 1)
	{
		if ((infos->cursor.x >= x && infos->cursor.x <= x + w) &&
			(infos->cursor.y >= y && infos->cursor.y <= y + h) &&
				infos->keys.left_click == 1)
		{
			infos->button[id].press = 1;
			return (1);
		}
		else if ((infos->cursor.x >= x && infos->cursor.x <= x + w) &&
			(infos->cursor.y >= y && infos->cursor.y <= y + h) &&
				infos->keys.left_click == 0 && infos->button[id].press == 1)
			return (2);
		else if (((infos->cursor.x < x || infos->cursor.x > x + w) ||
			(infos->cursor.y < y || infos->cursor.y > y + h)) ||
				infos->keys.left_click == 0)
			infos->button[id].press = 0;
	}
	return (0);
}

void		ft_print_yn_button(t_window *infos)
{
	if (infos->edit_button[0].press == 0)
		ft_button_yn_in_game(infos, 0, infos->edit_button[0].button_up);
	else
		ft_button_yn_in_game(infos, 0, infos->edit_button[0].button_down);
	if (infos->edit_button[1].press == 0)
		ft_button_yn_in_game(infos, 1, infos->edit_button[1].button_up);
	else
		ft_button_yn_in_game(infos, 1, infos->edit_button[1].button_down);
}

static void	ft_print_button(t_window *infos)
{
	if (infos->button[0].press == 0)
		ft_button_in_game(infos, 0, infos->button[0].button_up);
	else
		ft_button_in_game(infos, 0, infos->button[0].button_down);
	if (infos->button[1].press == 0)
		ft_button_in_game(infos, 1, infos->button[1].button_up);
	else
		ft_button_in_game(infos, 1, infos->button[1].button_down);
	if (infos->button[2].press == 0)
		ft_button_in_game(infos, 2, infos->button[2].button_up);
	else
		ft_button_in_game(infos, 2, infos->button[2].button_down);
	if (infos->button[3].press == 0)
		ft_button_in_game(infos, 3, infos->button[3].button_up);
	else
		ft_button_in_game(infos, 3, infos->button[3].button_down);
}

void		ft_putmenu(t_window *infos)
{
	int			i;
	t_coord2d	coord;

	i = 0;
	coord.x = WIDTH / 2 - infos->title.w / 2;
	coord.y = 40;
	ft_img_in_game(infos->game, infos->title, coord, 1);
	ft_rotate_left(infos, 0.01);
	mlx_string_put(infos->mlx_ptr, infos->win_ptr, WIDTH *
		0.6, HEIGHT * 0.1, 0xFFFFFF, infos->map.name);
	while (i < 4)
	{
		if (ft_manage_button(infos, infos->button[i].x,
			infos->button[i].y, i) == 2)
			ft_act_button(infos, i);
		i++;
	}
	ft_manage_rd_bt(infos);
	if (infos->map_menu == 1)
		ft_check_map(infos);
	ft_print_button(infos);
}
