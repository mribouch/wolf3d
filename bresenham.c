/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 18:13:11 by mribouch          #+#    #+#             */
/*   Updated: 2019/07/03 17:52:30 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <math.h>

int             ft_lerp(int i, int color1, int color2, float nbp)
{
        t_color c1;
        t_color c2;
        t_color c3;
        int             ret;

        c1.r = (color1 & 0xFF0000) >> 16;
        c1.g = (color1 & 0x00FF00) >> 8;
        c1.b = (color1 & 0x0000FF);
        c2.r = (color2 & 0xFF0000) >> 16;
        c2.g = (color2 & 0x00FF00) >> 8;
        c2.b = (color2 & 0x0000FF);
        c3.r = c1.r + (c2.r - c1.r) * (i - 0) / (nbp - 0);
        c3.g = c1.g + (c2.g - c1.g) * (i - 0) / (nbp - 0);
        c3.b = c1.b + (c2.b - c1.b) * (i - 0) / (nbp - 0);
        ret = (c3.b << 0) | (c3.g << 8) | (c3.r << 16);
        return (ret);
}

static int	*ft_fill_pixel_new(t_window *infos, t_var c, t_bresen b, float nbp)
{
	int		i;
	float	x;
	float	y;

	x = b.x;
	y = b.y;
	i = (int)x + (int)y * infos->width;
	if (x >= infos->width || y >= infos->height || x < 0 || y < 0)
		;
	else
		infos->img[i] = ft_lerp(b.i, c.color1, c.color2, nbp);
	return (infos->img);
}

static void	ft_sec_c(t_bresen *b, t_window *infos, t_coord2d v1, t_coord2d v2)
{
	t_var	c;

	c.color1 = v1.color;
	c.color2 = v2.color;
	b->cumul = b->dy / 2;
	b->i = 1;
	while (b->i++ <= b->dy)
	{
		b->y += b->yinc;
		b->cumul += b->dx;
		if (b->cumul >= b->dy)
		{
			b->cumul -= b->dy;
			b->x += b->xinc;
		}
		infos->img = ft_fill_pixel_new(infos, c, *b, b->dy);
	}
}

static void	ft_first_c(t_bresen *b, t_window *infos, t_coord2d v1, t_coord2d v2)
{
	t_var	c;

	c.color1 = v1.color;
	c.color2 = v2.color;
	b->cumul = b->dx / 2;
	while (b->i++ <= b->dx)
	{
		b->x += b->xinc;
		b->cumul += b->dy;
		if (b->cumul >= b->dx)
		{
			b->cumul -= b->dx;
			b->y += b->yinc;
		}
		infos->img = ft_fill_pixel_new(infos, c, *b, b->dx);
	}
}

void		ft_line_new(t_window *infos, t_coord2d v1, t_coord2d v2)
{
	t_bresen	b;
	t_var		c;

	c.color1 = v1.color;
	c.color2 = v2.color;
	b.x = v1.x;
	b.y = v1.y;
	b.dx = v2.x - v1.x;
	b.dy = v2.y - v1.y;
	b.i = 1;
	b.xinc = (b.dx > 0) ? 1 : -1;
	b.yinc = (b.dy > 0) ? 1 : -1;
	b.dx = fabsf(b.dx);
	b.dy = fabsf(b.dy);
	if (b.x > infos->width || b.y > infos->height || b.x < 0 || b.y < 0)
		;
	else
	{
		infos->img = ft_fill_pixel_new(infos, c, b, b.dx);
		if (b.dx > b.dy)
			ft_first_c(&b, infos, v1, v2);
		else
			ft_sec_c(&b, infos, v1, v2);
	}
}
