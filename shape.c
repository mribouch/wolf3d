/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 16:11:37 by mribouch          #+#    #+#             */
/*   Updated: 2020/01/13 14:37:03 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	ft_fill_circle(t_window *infos, t_coord2d c, int x, int y)
{
	infos->game.img[(int)(c.x + x) + (int)(c.y + y) * infos->game.w] = c.color;
	infos->game.img[(int)(c.x + y) + (int)(c.y + x) * infos->game.w] = c.color;
	infos->game.img[(int)(c.x - x) + (int)(c.y + y) * infos->game.w] = c.color;
	infos->game.img[(int)(c.x - y) + (int)(c.y + x) * infos->game.w] = c.color;
	infos->game.img[(int)(c.x + x) + (int)(c.y - y) * infos->game.w] = c.color;
	infos->game.img[(int)(c.x + y) + (int)(c.y - x) * infos->game.w] = c.color;
	infos->game.img[(int)(c.x - x) + (int)(c.y - y) * infos->game.w] = c.color;
	infos->game.img[(int)(c.x - y) + (int)(c.y - x) * infos->game.w] = c.color;
}

void		ft_fullcircle(t_window *infos, t_coord2d c, int r, int color)
{
	int	x;
	int	y;
	int	d;

	c.color = color;
	while (r >= 0)
	{
		x = 0;
		y = r;
		d = r - 1;
		while (y >= x)
		{
			ft_fill_circle(infos, c, x, y);
			if (d >= 2 * x)
				d -= 2 * x++ + 1;
			else if (d < 2 * (r - y))
				d += 2 * y-- - 1;
			else
				d += 2 * (y-- - x++ - 1);
		}
		r--;
	}
}
