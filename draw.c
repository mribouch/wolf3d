/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 16:58:17 by mribouch          #+#    #+#             */
/*   Updated: 2019/09/09 12:16:00 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

#include <stdio.h>
#include <math.h>


void	ft_draw_col(t_window *infos, int up, int dwn, int it)
{
	int	i;

	i = 0;
	while (i < HEIGHT)
	{
		if (infos->wolf.tab_ray[it].length == 100)
			infos->img[it + i++ * WIDTH] = 0x000000;
		else if (i < up)
		{
			infos->img[it + i++ * WIDTH] = 0x000000;
		}
		else if (i >= up && i <= dwn)
			infos->img[it + i++ * WIDTH] = 0xFF0000;
		else if (i > dwn)
			infos->img[it + i++ * WIDTH] = 0x000000;
	}
}

void	ft_draw_wolf(t_window *infos)
{
	int	i;
	int	dm2;
	int	hp;
	int intup;
	int	intdwn;

	i = 0;
	while (i < WIDTH)
	{
		dm2 = pow(infos->wolf.pos_cam.x - infos->wolf.tab_ray[i].pos_int.x, 2)
			+ pow(infos->wolf.pos_cam.y - infos->wolf.tab_ray[i].pos_int.y, 2);
		hp = (infos->wolf.d_camscreen) * 64 / sqrt(dm2);
		intup = (HEIGHT / 2 - (hp / 2));
		// printf("up = %d\ndwn = %d\n\n", intup, intdwn);
		intdwn = HEIGHT / 2 + (hp / 2);
		ft_draw_col(infos, intup, intdwn, i);
		i++;
	}
}

void	ft_draw_ray(t_window *infos)
{
	int	i;
	t_coord2d	pos_cam_mm;

	pos_cam_mm.x = 100;
	pos_cam_mm.y = 100;
	i = 0;
	while (i < WIDTH)
	{
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