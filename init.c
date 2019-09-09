/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 17:58:11 by mribouch          #+#    #+#             */
/*   Updated: 2019/08/19 14:37:46 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

#include <stdio.h>

#include <math.h>

void	ft_init_wolf(t_window *infos)
{
	if (!(infos->wolf.tab_ray = malloc(sizeof(t_ray) * (WIDTH))))
		return ;
	infos->wolf.angle_cam = 0.349066;
	infos->wolf.d_camscreen = (WIDTH / 2) / tan(1.0472 / 2);
	infos->wolf.pos_cam.x = 100;
	infos->wolf.pos_cam.y = 100;
	infos->wolf.dir_cam.x = cos(infos->wolf.angle_cam) * 50 + infos->wolf.pos_cam.x;
	infos->wolf.dir_cam.y = sin(infos->wolf.angle_cam) * 50 + infos->wolf.pos_cam.y;
	infos->wolf.dir_cam.color = 0x00FF00;
	infos->map.map_pos.x = 0;
	infos->map.map_pos.y = 0;
	ft_init_ray(infos);
	printf("address = %p\n", &infos->wolf.tab_ray);
}