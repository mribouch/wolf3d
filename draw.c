/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 16:58:17 by mribouch          #+#    #+#             */
/*   Updated: 2019/08/12 17:52:29 by mribouch         ###   ########.fr       */
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

void	ft_draw_minimap(t_window *infos, t_coord2d coordmap)
{
	t_square	sq;
	int			i;
	int			j;

	i = 0;
	j = 0;
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
			ft_fill_square(infos, sq);
			sq.x += sq.size;
			j++;
		}
		j = 0;
		i++;
		sq.x = sq.size / 2;
		sq.y += sq.size;
	}
}