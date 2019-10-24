/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 14:00:24 by mribouch          #+#    #+#             */
/*   Updated: 2019/10/24 18:04:23 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <math.h>

static void	ft_rotate_view(t_window *infos)
{
	double		olddirx;
	double		oldplanex;

	if (infos->keys.a == 1)
	{
		olddirx = infos->wolf.dir_cam.x;
		infos->wolf.dir_cam.x = infos->wolf.dir_cam.x * cos(0.05) - infos->wolf.dir_cam.y * sin(0.05);
		infos->wolf.dir_cam.y = olddirx * sin(0.05) + infos->wolf.dir_cam.y * cos(0.05);
		oldplanex = infos->wolf.plane.x;
		infos->wolf.plane.x = infos->wolf.plane.x * cos(0.05) - infos->wolf.plane.y * sin(0.05);
		infos->wolf.plane.y = oldplanex * sin(0.05) + infos->wolf.plane.y * cos(0.05);
	}
	if (infos->keys.d == 1)
	{
		olddirx = infos->wolf.dir_cam.x;
		infos->wolf.dir_cam.x = infos->wolf.dir_cam.x * cos(-0.05) - infos->wolf.dir_cam.y * sin(-0.05);
		infos->wolf.dir_cam.y = olddirx * sin(-0.05) + infos->wolf.dir_cam.y * cos(-0.05);
		oldplanex = infos->wolf.plane.x;
		infos->wolf.plane.x = infos->wolf.plane.x * cos(-0.05) - infos->wolf.plane.y * sin(-0.05);
		infos->wolf.plane.y = oldplanex * sin(-0.05) + infos->wolf.plane.y * cos(-0.05);
	}
}

static void	ft_walk(t_window *infos)
{
	if (infos->keys.w == 1)
	{
		if (infos->map.map[(int)infos->wolf.pos_cam.y][(int)(infos->wolf.pos_cam.x + infos->wolf.dir_cam.x * 0.05)] == 0)
			infos->wolf.pos_cam.x += infos->wolf.dir_cam.x * 0.05;
		if (infos->map.map[(int)(infos->wolf.pos_cam.y + infos->wolf.dir_cam.y * 0.05)][(int)infos->wolf.pos_cam.x] == 0)
			infos->wolf.pos_cam.y += infos->wolf.dir_cam.y * 0.05;
	}
	if (infos->keys.s == 1)
	{
		if (infos->map.map[(int)infos->wolf.pos_cam.y][(int)(infos->wolf.pos_cam.x - infos->wolf.dir_cam.x * 0.05)] == 0)
			infos->wolf.pos_cam.x -= infos->wolf.dir_cam.x * 0.05;
		if (infos->map.map[(int)(infos->wolf.pos_cam.y - infos->wolf.dir_cam.y * 0.05)][(int)infos->wolf.pos_cam.x] == 0)
			infos->wolf.pos_cam.y -= infos->wolf.dir_cam.y * 0.05;
	}
}

static void	ft_act_block(t_window *infos)
{
	int		x;
	int		y;
	double	camx;

	if (infos->keys.right_click == 1 && infos->wolf.editor == 1)
	{
		camx = 2 * (WIDTH / 2) / (double)infos->width - 1;
		x = infos->wolf.pos_cam.x + infos->wolf.dir_cam.x * infos->wolf.edit_distance_wall + infos->wolf.plane.x * camx;
		y = infos->wolf.pos_cam.y + infos->wolf.dir_cam.y * infos->wolf.edit_distance_wall + infos->wolf.plane.y * camx;
		if ((x > 0 && x < infos->map.width) && (y > 0 && y < infos->map.height))
			infos->map.map[y][x] = infos->wolf.select_block + 1;
	}
	if (infos->keys.left_click == 1 && infos->wolf.editor == 1)
	{
		x = infos->wolf.pos_cam.x + infos->wolf.dir_cam.x * infos->wolf.edit_distance_wall + infos->wolf.plane.x * camx;
		y = infos->wolf.pos_cam.y + infos->wolf.dir_cam.y * infos->wolf.edit_distance_wall + infos->wolf.plane.y * camx;
		if ((x > 0 && x < infos->map.width -1) && (y > 0 && y < infos->map.height - 1))
					infos->map.map[y][x] = 0;
	}
}

void	ft_dealk_act(t_window *infos)
{
	ft_walk(infos);
	ft_rotate_view(infos);
	// if (infos->keys.mouse_wheel_up == 1 && infos->wolf.edit_distance_wall < 7)
	// 	infos->wolf.edit_distance_wall++;
	// else if (infos->keys.mouse_wheel_down == 1 && infos->wolf.edit_distance_wall > 1)
	// 	infos->wolf.edit_distance_wall--;
	if (infos->keys.mouse_wheel_up == 1)
	{
		// ft_putendl("j'arrivededand ?");
		if (infos->wolf.select_block == 0)
			infos->wolf.select_block = 9;
		infos->wolf.select_block--;
	}
	if (infos->keys.mouse_wheel_down == 1)
	{
		if (infos->wolf.select_block == 8)
			infos->wolf.select_block = -1;
		infos->wolf.select_block++;
	}
	if (infos->keys.i == 1)
		infos->wolf.editor = 1;
	if (infos->keys.o == 1)
		infos->wolf.editor = 0;
	if (infos->wolf.editor == 0)
		if (infos->map.map[(int)infos->wolf.old_block.y][(int)infos->wolf.old_block.x] == 3)
			infos->map.map[(int)infos->wolf.old_block.y][(int)infos->wolf.old_block.x] = 0;
	ft_act_block(infos);
	infos->keys.mouse_wheel_up = 0;
	infos->keys.mouse_wheel_down = 0;
}