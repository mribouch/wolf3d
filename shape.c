/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 16:11:37 by mribouch          #+#    #+#             */
/*   Updated: 2019/11/12 16:17:47 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"


#include <stdio.h>

void		ft_square(t_window *infos, t_image img, t_square s)
{
	int	i;
	int	j;

	i = s.x;
	j = s.y;
	(void)infos;
	{
		while (i < s.x + s.size)
			img.img[i++ + s.y * img.w] = s.color;
		while (j < s.y + s.size)
			img.img[i + j++ * img.w] = s.color;
		while (i > s.x)
			img.img[i-- + j * img.w] = s.color;
		while (j > s.y)
			img.img[s.x + j-- * img.w] = s.color;
	}
}

void		ft_fill_square(t_window *infos, t_image img, t_square s)
{
	int	i;
	int	j;

	i = s.x;
	j = s.y;
	while (j < s.y + s.size)
	{
		while (i < s.x + s.size)
			img.img[i++ + j * img.w] = s.color;
		i = s.x;
		j++;
	}
	if (s.color == 0x000000 || s.color == 0xFFFFFF)
	{
		if (s.color == 0x000000)
			s.color = 0xFFFFFF;
		else
			s.color = 0x000000;
		s.x -= 1;
		s.y -= 1;
		s.size += 1;
		ft_square(infos, img, s);
	}
}

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

void		ft_circle(t_window *infos, t_coord2d c, int r, int color)
{
	int	x;
	int	y;
	int	d;

	c.color = color;
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
}
