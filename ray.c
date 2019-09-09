/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 16:13:18 by mribouch          #+#    #+#             */
/*   Updated: 2019/09/09 17:19:41 by mribouch         ###   ########.fr       */
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

int		ft_intersect(t_window *infos, int it)
{
	float		angle;
	t_coord2d	dir_vec;
	int			l;
	float		dx;
	float		dy;

	l = 0;
	angle = infos->wolf.angle_cam + 1.0472 / 2 - it * (1.0472 / WIDTH);
	dir_vec.x = cosf(angle);
	dir_vec.y = sinf(angle);
	while (l < 100)
	{
		dx = infos->wolf.pos_cam.x + l * dir_vec.x;
		dy = infos->wolf.pos_cam.y + l * dir_vec.y;
		infos->wolf.tab_ray[it].pos_int.x = dx;
		infos->wolf.tab_ray[it].pos_int.y = dy;
		// printf("dx = %f\ndy = %f\n\n", dx, dy);
		if (ft_check_wall(infos->map, dx/24, dy/24) == 1)
		{
			// ft_putendl("murrrrrrrr");
			return (l);
		}
		l++;
	}
	// printf("dafuuuuu\n");
	return (-1);
}

void	ft_update_ray(t_window *infos)
{
	int	i;
	int	l;

	i = 0;
	while (i < WIDTH)
	{
		if ((l = ft_intersect(infos, i)) > 0)
			infos->wolf.tab_ray[i].length = l;
		else
			infos->wolf.tab_ray[i].length = 100;
		infos->wolf.tab_ray[i].pos_ray.x = infos->wolf.pos_cam.x + infos->wolf.tab_ray[i].length
			* cosf((infos->wolf.angle_cam + 1.0472 / 2) - i * (1.0472 / WIDTH));
		infos->wolf.tab_ray[i].pos_ray.y = infos->wolf.pos_cam.y + infos->wolf.tab_ray[i].length
			* sinf((infos->wolf.angle_cam + 1.0472 / 2) - i * (1.0472 / WIDTH));
		i++;
	}
}

void	ft_init_ray(t_window *infos)
{
	int	i;

	i = 0;
	ft_putendl("nanibefore");
	while (i < WIDTH)
	{
		infos->wolf.tab_ray[i].length = 100;
		infos->wolf.tab_ray[i].pos_ray.x = infos->wolf.pos_cam.x + infos->wolf.tab_ray[i].length
			* cosf((infos->wolf.angle_cam + 1.0472 / 2) - i * (1.0472 / WIDTH));
		infos->wolf.tab_ray[i].pos_ray.y = infos->wolf.pos_cam.y + infos->wolf.tab_ray[i].length
			* sinf((infos->wolf.angle_cam + 1.0472 / 2) - i * (1.0472 / WIDTH));
		infos->wolf.tab_ray[i].pos_ray.color = 0x00FF00;
		i++;
	}
	// exit(0);
	ft_putendl("naniafter");
}