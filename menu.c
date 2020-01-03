/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 14:49:28 by mribouch          #+#    #+#             */
/*   Updated: 2019/12/04 17:07:29 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#    include <math.h>
#   include <stdio.h>

void	ft_img_in_game(t_image main, t_image print, t_coord2d coord, int coef)
{
	t_coord2d	tmp;
	t_coord2d	iter;
	int	itcoef;
	int	tmpitcoef;
	int	tmpcoef;

	tmp.y = coord.y;
	tmp.x = coord.x;
	iter.x = 0;
	iter.y = 0;
	itcoef = 0;
	tmpcoef = 0;
	tmpitcoef = 0;
	while (tmp.y < coord.y + (print.h * coef))
	{
		while (tmp.x < (coord.x + print.w * coef))
		{
			while (itcoef < coef)
			{
				while (tmpitcoef < coef)
				{
					// printf("color = %d\n", print.img[iter.x + iter.y * print.w]);
					if (print.img[(int)(iter.x + iter.y * print.w)] >= 0x000000)
						main.img[(int)(tmp.x + itcoef + (tmp.y + tmpitcoef) * WIDTH)] = print.img[(int)(iter.x + iter.y * print.w)];
					tmpitcoef++;
				}
				itcoef++;
				tmpitcoef = 0;
			}
			itcoef = 0;
			tmp.x += coef;
			iter.x++;
		}
		tmp.x = coord.x;
		iter.x = 0;
		tmp.y += coef;
		iter.y++;
	}

}

static void	ft_button_yn_in_game(t_window *infos, int id, t_image up_down)
{
	int	i;
	int	j;
	int	a;
	int	b;

	i = infos->edit_button[id].y;
	j = infos->edit_button[id].x;
	a = 0;
	b = 0;
	while (i < infos->edit_button[id].y + infos->edit_button[id].button_up.h)
	{
		while (j < infos->edit_button[id].x + infos->edit_button[id].button_up.w)
		{
			infos->game.img[j + i * WIDTH] = up_down.img[a + b * infos->edit_button[id].button_up.w];
			j++;
			a++;
		}
		j = infos->edit_button[id].x;
		a = 0;
		i++;
		b++;
	}
}

static void	ft_button_in_game(t_window *infos, int id, t_image up_down)
{
	int	i;
	int	j;
	int	a;
	int	b;

	i = infos->button[id].y;
	j = infos->button[id].x;
	a = 0;
	b = 0;
	while (i < infos->button[id].y + infos->button[id].button_up.h)
	{
		while (j < infos->button[id].x + infos->button[id].button_up.w)
		{
			infos->game.img[j + i * WIDTH] = up_down.img[a + b * infos->button[id].button_up.w];
			j++;
			a++;
		}
		j = infos->button[id].x;
		a = 0;
		i++;
		b++;
	}
}

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
		ft_edit(infos);
		infos->map_menu = 0;
	}
	if (id == 3)
		exit(0);
}

static int		ft_manage_button(t_window *infos, int x, int y, int id)
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
			(infos->cursor.y < y || infos->cursor.y > y + h)) || infos->keys.left_click == 0)
				infos->button[id].press = 0;
	}
	return (0);
}

void	ft_print_yn_button(t_window *infos)
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

static void	ft_rotate_bg(t_window *infos)
{
	double		olddirx;
	double		oldplanex;
	double		speed;

	speed = 0.01;
	olddirx = infos->wolf.dir_cam.x;
	infos->wolf.dir_cam.x = infos->wolf.dir_cam.x * cos(speed) - infos->wolf.dir_cam.y * sin(speed);
	infos->wolf.dir_cam.y = olddirx * sin(speed) + infos->wolf.dir_cam.y * cos(speed);
	oldplanex = infos->wolf.plane.x;
	infos->wolf.plane.x = infos->wolf.plane.x * cos(speed) - infos->wolf.plane.y * sin(speed);
	infos->wolf.plane.y = oldplanex * sin(speed) + infos->wolf.plane.y * cos(speed);
}

void	ft_putmenu(t_window *infos)
{
	int	i;
	t_coord2d	coord;

	i = 0;
	coord.x = WIDTH / 2 - infos->title.w / 2;
	coord.y = 40;
	ft_img_in_game(infos->game, infos->title, coord, 1);
	// ft_img_in_game(infos->game, infos->texture[7], 20, 20, 10);
	ft_rotate_bg(infos);
	mlx_string_put(infos->mlx_ptr, infos->win_ptr, WIDTH * 0.6, HEIGHT * 0.1, 0xFFFFFF, infos->map.name);
	while (i < 4)
	{
		if (ft_manage_button(infos, infos->button[i].x, infos->button[i].y, i) == 2)
			ft_act_button(infos, i);
		i++;
	}
	ft_manage_rd_bt(infos);
	if (infos->map_menu == 1)
		ft_check_map(infos);
	// ft_putendl("avant print button");
	ft_print_button(infos);
	// ft_putendl("apres print button");
}