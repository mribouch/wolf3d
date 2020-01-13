/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 15:06:11 by mribouch          #+#    #+#             */
/*   Updated: 2020/01/13 19:28:46 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	ft_break_wall(t_window *infos)
{
	int		x;
	int		y;
	double	camx;

	camx = 2 * (WIDTH / 2) / (double)WIDTH - 1;
	x = infos->wolf.pos_cam.x + infos->wolf.dir_cam.x
		* infos->wolf.edit_distance_wall + infos->wolf.plane.x * camx;
	y = infos->wolf.pos_cam.y + infos->wolf.dir_cam.y
		* infos->wolf.edit_distance_wall + infos->wolf.plane.y * camx;
	if ((x > 0 && x < infos->map.width - 1)
		&& (y > 0 && y < infos->map.height - 1))
		infos->map.map[y][x] = 0;
}

void	ft_put_wall(t_window *infos)
{
	int		x;
	int		y;
	double	camx;

	camx = 2 * (WIDTH / 2) / (double)WIDTH - 1;
	x = infos->wolf.pos_cam.x + infos->wolf.dir_cam.x
		* infos->wolf.edit_distance_wall + infos->wolf.plane.x * camx;
	y = infos->wolf.pos_cam.y + infos->wolf.dir_cam.y
		* infos->wolf.edit_distance_wall + infos->wolf.plane.y * camx;
	if ((x > 0 && x < infos->map.width) && (y > 0 && y < infos->map.height))
		infos->wolf.old_block.color = 1;
}

void	ft_rotate_right(t_window *infos, float speed)
{
	double	olddirx;
	double	oldplanex;

	speed = -speed;
	olddirx = infos->wolf.dir_cam.x;
	infos->wolf.dir_cam.x = infos->wolf.dir_cam.x * cos(speed)
		- infos->wolf.dir_cam.y * sin(speed);
	infos->wolf.dir_cam.y = olddirx * sin(speed)
		+ infos->wolf.dir_cam.y * cos(speed);
	oldplanex = infos->wolf.plane.x;
	infos->wolf.plane.x = infos->wolf.plane.x * cos(speed)
		- infos->wolf.plane.y * sin(speed);
	infos->wolf.plane.y = oldplanex * sin(speed)
		+ infos->wolf.plane.y * cos(speed);
}

void	ft_rotate_left(t_window *infos, float speed)
{
	double	olddirx;
	double	oldplanex;

	olddirx = infos->wolf.dir_cam.x;
	infos->wolf.dir_cam.x = infos->wolf.dir_cam.x * cos(speed)
		- infos->wolf.dir_cam.y * sin(speed);
	infos->wolf.dir_cam.y = olddirx * sin(speed)
		+ infos->wolf.dir_cam.y * cos(speed);
	oldplanex = infos->wolf.plane.x;
	infos->wolf.plane.x = infos->wolf.plane.x * cos(speed)
		- infos->wolf.plane.y * sin(speed);
	infos->wolf.plane.y = oldplanex * sin(speed)
		+ infos->wolf.plane.y * cos(speed);
}

void	ft_rotate_view(t_window *infos, float speed)
{
	if (infos->keys.a == 1)
		ft_rotate_left(infos, speed);
	if (infos->keys.d == 1)
		ft_rotate_right(infos, speed);
}
