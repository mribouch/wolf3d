/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 16:58:17 by mribouch          #+#    #+#             */
/*   Updated: 2019/10/15 17:20:56 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

#include <stdio.h>
#include <math.h>


void	ft_draw_col(t_window *infos, float up, float dwn, int it)
{
	int	i;

	i = 0;
	while (i < HEIGHT)
	{
		if (infos->wolf.tab_ray[it].length == RAYLENGHT)
		{
			if (i <= HEIGHT / 2)
				infos->img[WIDTH - it + i++ * WIDTH] = 0x392C02;
			else
				infos->img[WIDTH - it + i++ * WIDTH] = 0x765E10;
		}
		else if (i < (int)up)
		{
			infos->img[WIDTH - it + i++ * WIDTH] = 0x392C02;
		}
		else if (i >= (int)up && i <= (int)dwn)
			infos->img[WIDTH - it + i++ * WIDTH] = 0xB8B8B8;
		else if (i > (int)dwn)
			infos->img[WIDTH - it + i++ * WIDTH] = 0x765E10;
			// printf("voici i = %d\n", i);
	}
}

void	ft_draw_wolf(t_window *infos, t_dda dda, double perp_wall_dist, int x)
{
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	color;
	int	i;
	(void)dda;
	// perp_wall_dist += 0.00000001;
	color = 0xFFFFFF;
	// ft_putendl("perpwall = ");
	// ft_putnbr(perp_wall_dist);
	line_height = (int)(HEIGHT / perp_wall_dist);
	// ft_putendl("\nlineheight = ");
	// ft_putnbr(line_height);
	draw_start = -line_height / 2 + HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + HEIGHT / 2;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	if (dda.side == 1)
		color = 0xDDDDDD;
	i = draw_start;
	while(i < draw_end)
	{
		infos->img[x + i++ * WIDTH] = color;
	}
}

void	ft_draw_ray(t_window *infos)
{
	int	i;
	t_coord2d	pos_cam_mm;

	pos_cam_mm.x = 100;
	pos_cam_mm.y = 100;
	pos_cam_mm.color = 0x00FF00;
	i = 0;
	while (i < WIDTH)
	{
		// infos->wolf.tab_ray[i].length /= cos(infos->wolf.tab_ray[i].angle);
		infos->wolf.tab_ray[i].pos_ray.x -= (infos->wolf.pos_cam.x - pos_cam_mm.x);
		infos->wolf.tab_ray[i].pos_ray.y -= (infos->wolf.pos_cam.y - pos_cam_mm.y);
		ft_line_new(infos, pos_cam_mm, infos->wolf.tab_ray[i].pos_ray);
		i++;
	}
}

void	ft_draw_cam(t_window *infos)
{
	t_coord2d	coordcam;

	// coordcam.x = infos->wolf.pos_cam.x;
	// coordcam.y = infos->wolf.pos_cam.y;
	coordcam.x = 100;
	coordcam.y = 100;
	coordcam.color = 0xDD1212;
	ft_fullcircle(infos, coordcam, 3, 0xDD1212);
}

void	ft_draw_fence(t_window *infos)
{
	t_square	fence;

	fence.size = 200;
	fence.x = 0;
	fence.y = 0;
	fence.color = 0xFF0000;
	ft_square(infos, fence);
}

void	ft_draw_minimap(t_window *infos, t_coord2d coordmap)
{
	t_square	sq;
	int			i;
	int			j;

	i = 0;
	j = 0;
	ft_draw_fence(infos);
	sq.size = 24;
	sq.x = coordmap.x;
	sq.y = coordmap.y;
	while (i < infos->map.height)
	{
		while (j < infos->map.width)
		{
			if (infos->map.map[i][j] == 0)
				sq.color = 0xFFFFFF;
			else
				sq.color = 0x0000FF;
			if ((sq.x < 200 - sq.size && sq.x >= 0) && (sq.y < 200 - sq.size && sq.y >= 0))
				ft_fill_square(infos, sq);
			sq.x += sq.size;
			j++;
		}
		j = 0;
		i++;
		sq.x = coordmap.x;
		sq.y += sq.size;
	}
}