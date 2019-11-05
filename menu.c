/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 14:49:28 by mribouch          #+#    #+#             */
/*   Updated: 2019/11/05 18:23:43 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#    include <math.h>
#   include <stdio.h>
// int	*ft_fill_menu(t_window *infos, int x, int y, t_image button)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	j = 0;
// 	while (i < button.h)
// 	{
// 		while (j < button.w)
// 		{
// 			infos->menu.img[(x + j) + (y + i) * WIDTH] = button.img[j + i * button.w];
// 			j++;
// 		}
// 		j = x;
// 		i++;
// 	}
// 	return (infos->menu.img);
// }

void	ft_rotate_bg(t_window *infos)
{
	double		olddirx;
	double		oldplanex;
	double		speed;

	speed = 0.01;
	olddirx = infos->wolf.dir_cam.x;
	infos->wolf.dir_cam.x = infos->wolf.dir_cam.x * cos(speed) - infos->wolf.dir_cam.y * sin(speed);
	infos->wolf.dir_cam.y = olddirx * sin(speed) + infos->wolf.dir_cam.y * cos(speed);
	oldplanex = infos->wolf.plane.x;
	infos->wolf.plane.x = infos->wolf.plane.x * cos(speed) - infos->wolf.plane.y * sin(speed);
	infos->wolf.plane.y = oldplanex * sin(speed) + infos->wolf.plane.y * cos(speed);
}

void	ft_putmenu(t_window *infos)
{
	int	x;
	int	y;
	int	h;
	int	w;
	int	down;

	h = infos->button[0].h;
	w = infos->button[0].w;
	ft_rotate_bg(infos);
	down = 0;
	// infos->menu.img = ft_fill_menu(infos, x, y, infos->button[0]);
	x = WIDTH / 2 - w / 2;
	y = HEIGHT * 0.25 - h / 2;
	if (ft_manage_button(infos, x, y, 0) == 1)
		down++;
	if (ft_manage_button(infos, x, y, 0) == 2)
		infos->wolf.menu = 0;
	mlx_put_image_to_window(infos->mlx_ptr, infos->win_ptr, infos->button[0 + down].img_ptr, x, y);
	down = 0;
	y = HEIGHT * 0.4 - h / 2;
	if (ft_manage_button(infos, x, y, 2) == 1)
		down++;
	mlx_put_image_to_window(infos->mlx_ptr, infos->win_ptr, infos->button[2 + down].img_ptr, x, y);
	down = 0;
	y = HEIGHT * 0.55 - h / 2;
	if (ft_manage_button(infos, x, y, 4) == 1)
		down++;
	if (ft_manage_button(infos, x, y, 4) == 2)
	{
		printf("eeeeeeeh coucou");
		ft_edit(infos);

	}
	mlx_put_image_to_window(infos->mlx_ptr, infos->win_ptr, infos->button[4 + down].img_ptr, x, y);
	down = 0;
	y = HEIGHT * 0.70 - h / 2;
	if (ft_manage_button(infos, x, y, 6) == 1)
		down++;
	mlx_put_image_to_window(infos->mlx_ptr, infos->win_ptr, infos->button[6 + down].img_ptr, x, y);
}