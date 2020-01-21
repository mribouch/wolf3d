/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 16:45:17 by mribouch          #+#    #+#             */
/*   Updated: 2020/01/21 17:53:44 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_dda	ft_get_wall_color(t_window *infos, t_dda dda, int x, int tex_num)
{
	int	color;
	int	i;

	i = dda.draw_start;
	while (i < dda.draw_end)
	{
		dda.d = i * 256 - HEIGHT * 128 + dda.line_height * 128;
		dda.tex_y = ((dda.d * infos->texture[tex_num].h) /
			dda.line_height) / 256;
		color = infos->texture[tex_num].img[infos->texture[tex_num].h *
			dda.tex_y + dda.tex_x];
		if (dda.side == 1)
			color = (color >> 1) & 8355711;
		if ((int)infos->wolf.tnt_block.x == (int)dda.map.x &&
			(int)infos->wolf.tnt_block.y == (int)dda.map.y &&
				infos->wolf.explode == 1)
			color = ft_get_lerp_tnt(infos, color, 0xFFFFFF, 100 / 4);
		infos->wolf.block_dist = dda.perp_wall_dist;
		color = ft_get_lerp_dist(infos, color, infos->wolf.block_dist, 2);
		infos->game.img[x + i++ * WIDTH] = color;
	}
	return (dda);
}

t_dda	ft_get_floor_wall(t_window *infos, t_dda dda)
{
	(void)infos;
	if (dda.side == 0 && dda.raydir.x > 0)
	{
		dda.floor_wall.x = dda.map.x;
		dda.floor_wall.y = dda.map.y + dda.wall_x;
	}
	else if (dda.side == 0 && dda.raydir.x < 0)
	{
		dda.floor_wall.x = dda.map.x + 1.0;
		dda.floor_wall.y = dda.map.y + dda.wall_x;
	}
	else if (dda.side == 1 && dda.raydir.y > 0)
	{
		dda.floor_wall.x = dda.map.x + dda.wall_x;
		dda.floor_wall.y = dda.map.y;
	}
	else
	{
		dda.floor_wall.x = dda.map.x + dda.wall_x;
		dda.floor_wall.y = dda.map.y + 1.0;
	}
	dda.distwall = dda.perp_wall_dist;
	dda.distplayer = 0.0;
	return (dda);
}

void	ft_get_ceil_floor(t_window *infos, int x, int y, t_dda dda)
{
	int	color;

	while (y < HEIGHT)
	{
		dda.cur_dist = (double)(HEIGHT / (2.0 * y - HEIGHT));
		dda.weight = (dda.cur_dist - dda.distplayer) /
			(dda.distwall - dda.distplayer);
		dda.cur_floor.x = dda.weight * dda.floor_wall.x +
			(1.0 - dda.weight) * infos->wolf.pos_cam.x;
		dda.cur_floor.y = dda.weight * dda.floor_wall.y +
			(1.0 - dda.weight) * infos->wolf.pos_cam.y;
		dda.floor_tex.x = (int)(dda.cur_floor.x * infos->texture[2].w * 2) %
			infos->texture[2].w;
		dda.floor_tex.y = (int)(dda.cur_floor.y * infos->texture[2].h * 2) %
			infos->texture[2].h;
		color = (infos->texture[2].img[infos->texture[2].w *
			(int)dda.floor_tex.y + (int)dda.floor_tex.x]);
		color = ft_get_lerp_dist(infos, color, dda.cur_dist, 2);
		infos->game.img[x + y * WIDTH] = color;
		color = infos->texture[2].img[infos->texture[2].w *
			(int)dda.floor_tex.y + (int)dda.floor_tex.x];
		color = ft_get_lerp_dist(infos, color, dda.cur_dist, 2);
		infos->game.img[x + (HEIGHT - y) * WIDTH] = color;
		y++;
	}
}

void	ft_get_col_tex(t_window *infos, t_dda dda, int x, int tex_num)
{
	int		i;
	int		y;
	float	tex_x;

	i = 0;
	if (dda.side == 0)
		dda.wall_x = infos->wolf.pos_cam.y + dda.perp_wall_dist * dda.raydir.y;
	else
		dda.wall_x = infos->wolf.pos_cam.x + dda.perp_wall_dist * dda.raydir.x;
	dda.wall_x -= floorf(dda.wall_x);
	dda.tex_x = (int)(dda.wall_x * infos->texture[tex_num].w);
	tex_x = infos->texture[tex_num].w - dda.tex_x - 1;
	if ((dda.side == 0 && dda.raydir.x > 0) ||
		(dda.side == 1 && dda.raydir.y < 0))
		dda.tex_x = tex_x;
	i = dda.draw_start;
	dda = ft_get_wall_color(infos, dda, x, tex_num);
	dda = ft_get_floor_wall(infos, dda);
	if (dda.draw_end < 0)
		dda.draw_end = HEIGHT;
	y = dda.draw_end;
	ft_get_ceil_floor(infos, x, y, dda);
}
