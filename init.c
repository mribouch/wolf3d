/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 17:58:11 by mribouch          #+#    #+#             */
/*   Updated: 2019/08/13 17:01:35 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

#include <stdio.h>

#include <math.h>

void	ft_init_wolf(t_window *infos)
{
	infos->wolf.angle_cam = 0.349066;
	infos->wolf.pos_cam.x = 10;
	infos->wolf.pos_cam.y = 10;
	infos->wolf.dir_cam.x = cos(infos->wolf.angle_cam) * 50 + infos->wolf.pos_cam.x;
	infos->wolf.dir_cam.y = sin(infos->wolf.angle_cam) * 50 + infos->wolf.pos_cam.y;
	infos->wolf.dir_cam.color = 0x00FF00;
	infos->map.map_pos.x = WIDTH - 201;
	infos->map.map_pos.y = 0;
	// printf("poscamx = %f\n", cos(infos->wolf.angle_cam));
	// printf("poscamy = %f\n", infos->wolf.pos_cam.y);
}