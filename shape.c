/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 16:11:37 by mribouch          #+#    #+#             */
/*   Updated: 2019/08/12 17:06:07 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		ft_square(t_window *infos, t_square s)
{
	int	i;
	int	j;

	i = s.x;
	j = s.y;
	while (i < s.x + s.size)
		infos->img[i++ + s.y * infos->width] = s.color;
	while (j < s.y + s.size)
		infos->img[i + j++ * infos->width] = s.color;
	while (i > s.x)
		infos->img[i-- + j * infos->width] = s.color;
	while (j > s.y)
		infos->img[s.x + j-- * infos->width] = s.color;
}

void		ft_fill_square(t_window *infos, t_square s)
{
	int	i;
	int	j;

	i = s.x;
	j = s.y;
	while (j < s.y + s.size)
	{
		while (i < s.x + s.size)
			infos->img[i++ + j * infos->width] = s.color;
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
		ft_square(infos, s);
	}
}

static void	ft_fill_circle(t_window *infos, t_coord2d c, int x, int y)
{
	infos->img[(int)(c.x + x) + (int)(c.y + y) * infos->width] = c.color;
	infos->img[(int)(c.x + y) + (int)(c.y + x) * infos->width] = c.color;
	infos->img[(int)(c.x - x) + (int)(c.y + y) * infos->width] = c.color;
	infos->img[(int)(c.x - y) + (int)(c.y + x) * infos->width] = c.color;
	infos->img[(int)(c.x + x) + (int)(c.y - y) * infos->width] = c.color;
	infos->img[(int)(c.x + y) + (int)(c.y - x) * infos->width] = c.color;
	infos->img[(int)(c.x - x) + (int)(c.y - y) * infos->width] = c.color;
	infos->img[(int)(c.x - y) + (int)(c.y - x) * infos->width] = c.color;
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
