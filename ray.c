/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 16:13:18 by mribouch          #+#    #+#             */
/*   Updated: 2019/10/15 16:51:30 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <math.h>
#include <stdio.h>

int		ft_check_wall(t_map map, float dx, float dy)
{
	if (map.map[(int)dy][(int)dx] != 0)
		return (1);
	return (0);
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

void	ft_update_ray(t_window *infos)
{
	int		i;
	double	perp_wall_dist;
	t_dda	dda;

	i = 0;
	while (i < WIDTH)
	{
		dda.cam.x = 2 * i / (double)infos->width - 1;
		dda.raydir.x = infos->wolf.dir_cam.x + infos->wolf.plane.x * dda.cam.x;
		dda.raydir.y = infos->wolf.dir_cam.y + infos->wolf.plane.y * dda.cam.x;
		dda.map.x = (int)infos->wolf.pos_cam.x;
		dda.map.y = (int)infos->wolf.pos_cam.y;
		dda.delta_dist.x = fabs(1 / dda.raydir.x);
		dda.delta_dist.y = fabs(1 / dda.raydir.y);
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
		dda = ft_intersect(infos, dda);
		// printf("mapx = %f, mapy = %f, posx = %f, posy = %f, stepx = %f, stepy = %f, raydirx = %f, raydiry = %f", dda.map.x, dda.map.y, infos->wolf.pos_cam.x, infos->wolf.pos_cam.y, dda.step.x, dda.step.y, dda.raydir.x, dda.raydir.y);
		// ft_putendl("\n");
		// ft_putstr("stepx , stepy = ");
		// ft_putnbr(dda.raydir.x);
		// ft_putstr(", ");
		// ft_putnbr(dda.raydir.y);
		if (dda.side == 0)
			perp_wall_dist = (dda.map.x - infos->wolf.pos_cam.x + (1 - dda.step.x) / 2) / dda.raydir.x;
		else
			perp_wall_dist = (dda.map.y - infos->wolf.pos_cam.y + (1 -dda.step.y) / 2) / dda.raydir.y;
		// ft_putendl("avant le draw wolf");
		ft_draw_wolf(infos, dda, perp_wall_dist, i);
		// ft_putendl("apres le draw wolf");
		i++;
	}
}

void	ft_init_ray(t_window *infos)
{
	int	i;
	float	angle;
	float	fov;

	i = 0;
	angle = infos->wolf.angle_cam + FOV / 2;
	fov = FOV / WIDTH;
	ft_putendl("nanibefore");
	while (i < WIDTH)
	{
		infos->wolf.tab_ray[i].length = RAYLENGHT;
		infos->wolf.tab_ray[i].pos_ray.x = infos->wolf.pos_cam.x + infos->wolf.tab_ray[i].length
			* cosf(angle - i * fov);
		infos->wolf.tab_ray[i].angle = angle - i * fov;
		printf("ray numero %d, angle = %f\n", i, infos->wolf.tab_ray[i].angle);
		infos->wolf.tab_ray[i].pos_ray.y = infos->wolf.pos_cam.y + infos->wolf.tab_ray[i].length
			* sinf(angle - i * fov);
		infos->wolf.tab_ray[i].pos_ray.color = 0x00FF00;
		i++;
	}
	// exit(0);
	ft_putendl("naniafter");
}