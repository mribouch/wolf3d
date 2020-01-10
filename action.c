/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 14:00:24 by mribouch          #+#    #+#             */
/*   Updated: 2020/01/10 16:53:05 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	ft_walk(t_window *infos)
{
	if (infos->keys.w == 1)
	{
		if (infos->map.map[(int)infos->wolf.pos_cam.y]
			[(int)(infos->wolf.pos_cam.x + infos->wolf.dir_cam.x * 0.05)] == 0)
			infos->wolf.pos_cam.x += infos->wolf.dir_cam.x * 0.05;
		if (infos->map.map[(int)(infos->wolf.pos_cam.y
			+ infos->wolf.dir_cam.y * 0.05)][(int)infos->wolf.pos_cam.x] == 0)
			infos->wolf.pos_cam.y += infos->wolf.dir_cam.y * 0.05;
	}
	if (infos->keys.s == 1)
	{
		if (infos->map.map[(int)infos->wolf.pos_cam.y]
			[(int)(infos->wolf.pos_cam.x - infos->wolf.dir_cam.x * 0.05)] == 0)
			infos->wolf.pos_cam.x -= infos->wolf.dir_cam.x * 0.05;
		if (infos->map.map[(int)(infos->wolf.pos_cam.y
			- infos->wolf.dir_cam.y * 0.05)][(int)infos->wolf.pos_cam.x] == 0)
			infos->wolf.pos_cam.y -= infos->wolf.dir_cam.y * 0.05;
	}
}

static void	ft_act_block(t_window *infos)
{
	int		x;
	int		y;
	double	camx;

	camx = 2 * (WIDTH / 2) / (double)WIDTH - 1;
	if (infos->keys.right_click == 1 && infos->wolf.editor == 1)
		ft_put_wall(infos);
	if (infos->keys.left_click == 1 && infos->wolf.editor == 1)
		ft_break_wall(infos);
	if (infos->keys.right_click == 1 && infos->wolf.editor == 0
		&& infos->wolf.select_block == 7)
	{
		x = infos->wolf.pos_cam.x + infos->wolf.dir_cam.x
			* infos->wolf.edit_distance_wall + infos->wolf.plane.x * camx;
		y = infos->wolf.pos_cam.y + infos->wolf.dir_cam.y
			* infos->wolf.edit_distance_wall + infos->wolf.plane.y * camx;
		if (infos->map.map[y][x] == 6)
		{
			infos->wolf.explode = 1;
			infos->wolf.tnt_block.x = x;
			infos->wolf.tnt_block.y = y;
		}
	}
	if (infos->wolf.explode == 1)
		ft_explode_tnt(infos);
}

static void	ft_inventory_bar(t_window *infos)
{
	if (infos->keys.mouse_wheel_up == 1)
	{
		if (infos->wolf.select_block == 0)
			infos->wolf.select_block = 9;
		infos->wolf.select_block--;
		if (infos->wolf.editor == 1 && infos->wolf.select_block < 7)
			infos->map.map[(int)infos->wolf.old_block.y]
				[(int)infos->wolf.old_block.x] = infos->wolf.select_block + 1;
	}
	if (infos->keys.mouse_wheel_down == 1)
	{
		if (infos->wolf.select_block == 8)
			infos->wolf.select_block = -1;
		infos->wolf.select_block++;
		if (infos->wolf.editor == 1 && infos->wolf.select_block < 7)
			infos->map.map[(int)infos->wolf.old_block.y]
				[(int)infos->wolf.old_block.x] = infos->wolf.select_block + 1;
	}
}

void		ft_dealk_act(t_window *infos)
{
	ft_walk(infos);
	ft_rotate_view(infos, 0.03);
	ft_inventory_bar(infos);
	if (infos->keys.q == 1)
		infos->wolf.editor = 1;
	if (infos->keys.e == 1)
		infos->wolf.editor = 0;
	if (infos->wolf.editor == 0)
		if (infos->map.map[(int)infos->wolf.old_block.y]
			[(int)infos->wolf.old_block.x] > 0)
			infos->map.map[(int)infos->wolf.old_block.y]
				[(int)infos->wolf.old_block.x] = 0;
	ft_act_block(infos);
	infos->keys.mouse_wheel_up = 0;
	infos->keys.mouse_wheel_down = 0;
}
