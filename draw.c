/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 16:58:17 by mribouch          #+#    #+#             */
/*   Updated: 2019/08/13 17:33:43 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	ft_draw_cam(t_window *infos)
{
	t_coord2d	coordcam;

	coordcam.x = infos->wolf.pos_cam.x;
	coordcam.y = infos->wolf.pos_cam.y;
	coordcam.color = 0xDD1212;
	ft_fullcircle(infos, coordcam, 3, 0xDD1212);
}

void	ft_draw_fence(t_window *infos)
{
	t_square	fence;

	fence.size = 200;
	fence.x = WIDTH - 201;
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
			if ((sq.x < WIDTH - sq.size && sq.x >= WIDTH - 200) && (sq.y < 200 - sq.size && sq.y >= 0))
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