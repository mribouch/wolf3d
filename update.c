/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 16:13:18 by mribouch          #+#    #+#             */
/*   Updated: 2020/01/09 16:12:46 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	ft_editor(t_window *infos)
{
	t_coord2d	current_block;
	double	camx;

	camx = 2 * (WIDTH / 2) / (double)WIDTH - 1;
	current_block.x = infos->wolf.pos_cam.x + infos->wolf.dir_cam.x * infos->wolf.edit_distance_wall + infos->wolf.plane.x * camx;
	current_block.y = infos->wolf.pos_cam.y + infos->wolf.dir_cam.y * infos->wolf.edit_distance_wall + infos->wolf.plane.y * camx;
	if ((current_block.x <= 0 || current_block.x >= infos->map.width) ||
		(current_block.y <= 0 || current_block.y >= infos->map.height))
			return ;
	if (current_block.x != infos->wolf.old_block.x && current_block.y != infos->wolf.old_block.y)
	{
		// if (infos->map.map[(int)infos->wolf.old_block.y][(int)infos->wolf.old_block.x] != infos->wolf.select_block)
		if (infos->map.map[(int)current_block.y][(int)current_block.x] == 0)
		{
			if (infos->wolf.old_block.color == 0)
				infos->map.map[(int)infos->wolf.old_block.y][(int)infos->wolf.old_block.x] = 0;
			if (infos->wolf.select_block < 7)
				infos->map.map[(int)current_block.y][(int)current_block.x] = infos->wolf.select_block + 1;
			infos->wolf.old_block.x = current_block.x;
			infos->wolf.old_block.y = current_block.y;
			infos->wolf.old_block.color = 0;
		}
	}
}

t_dda		ft_intersect(t_window *infos, t_dda dda)
{
	dda.hit = 0;
	while (dda.hit == 0)
	{
		if (dda.side_dist.x < dda.side_dist.y)
		{
			dda.side_dist.x += dda.delta_dist.x;
			dda.map.x += dda.step.x;
			dda.side = 0;
		}
		else
		{
			dda.side_dist.y += dda.delta_dist.y;
			dda.map.y += dda.step.y;
			dda.side = 1;
		}
		if (infos->map.map[(int)dda.map.y][(int)dda.map.x] > 0)
			dda.hit = 1;
	}
	// ft_putendl("j'en sors ?");
	return (dda);
}

static t_dda	ft_get_side_dist(t_window *infos, t_dda dda)
{
	if (dda.raydir.x < 0)
	{
		dda.step.x = -1;
		dda.side_dist.x = (infos->wolf.pos_cam.x - dda.map.x) * dda.delta_dist.x;
	}
	else
	{
		dda.step.x = 1;
		dda.side_dist.x = (dda.map.x + 1.0 - infos->wolf.pos_cam.x) * dda.delta_dist.x;
	}
	if (dda.raydir.y < 0)
	{
		dda.step.y = -1;
		dda.side_dist.y = (infos->wolf.pos_cam.y - dda.map.y) * dda.delta_dist.y;
	}
	else
	{
		dda.step.y = 1;
		dda.side_dist.y = (dda.map.y + 1.0 - infos->wolf.pos_cam.y) * dda.delta_dist.y;
	}
	return (dda);
}

static void	ft_update_ray(t_window *infos)
{
	int		i;
	double	perp_wall_dist;
	t_dda	dda;

	i = 0;
	while (i < WIDTH)
	{
		dda.cam.x = 2 * i / (double)WIDTH - 1;
		dda.raydir.x = infos->wolf.dir_cam.x + infos->wolf.plane.x * dda.cam.x;
		dda.raydir.y = infos->wolf.dir_cam.y + infos->wolf.plane.y * dda.cam.x;
		dda.map.x = (int)infos->wolf.pos_cam.x;
		dda.map.y = (int)infos->wolf.pos_cam.y;
		dda.delta_dist.x = fabs(1 / dda.raydir.x);
		dda.delta_dist.y = fabs(1 / dda.raydir.y);
		dda = ft_get_side_dist(infos, dda);
		dda = ft_intersect(infos, dda);
		if (dda.side == 0)
			perp_wall_dist = (dda.map.x - infos->wolf.pos_cam.x + (1 - dda.step.x) / 2) / dda.raydir.x;
		else
			perp_wall_dist = (dda.map.y - infos->wolf.pos_cam.y + (1 -dda.step.y) / 2) / dda.raydir.y;
		// param->infos = infos;
		// param->dda = dda;
		// param->perp_wall_dist = perp_wall_dist;
		// param->i = i;
		ft_draw_wolf(infos, dda, perp_wall_dist, i);
		i++;
	}
}

void	ft_update(t_window *infos)
{
	ft_update_ray(infos);
	if (infos->wolf.editor == 1)
		ft_editor(infos);
	if (infos->wolf.menu == 0)
		ft_draw_cursor(infos);
	infos->wolf.dir_cam.color = 0xFF0000;
	if (infos->wolf.menu == 1)
		ft_putmenu(infos);
	if (infos->map_menu == 1)
		ft_print_rd_bt(infos);
	if (infos->save_map == 1)
	{
		if (ft_manage_yn_button(infos, infos->edit_button[0].x, infos->edit_button[0].y, 0) == 2)
		{
			ft_save(infos);
			ft_quit_wolf(infos);
			while(1);
			exit(0);
		}
		if (ft_manage_yn_button(infos, infos->edit_button[1].x, infos->edit_button[1].y, 1) == 2)
		{
			ft_quit_wolf(infos);
			while(1);
			exit(0);
		}
		ft_print_yn_button(infos);
	}
}