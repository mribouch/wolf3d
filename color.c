/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 15:57:45 by mribouch          #+#    #+#             */
/*   Updated: 2019/10/31 14:20:57 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		ft_hsv2rgb(t_hsv hsv)
{
    int		i;
    float	f;
    float	p;
    float	q;
    float	t;
    hsv.h = (hsv.h == 360) ? 0 : hsv.h / 60.0f;
    i = (int)hsv.h;
    f = hsv.h - i;
    p = hsv.v * (1.0f - hsv.s) * 255;
    q = hsv.v * (1.0f - (hsv.s * f)) * 255;
    t = hsv.v * (1.0f - (hsv.s * (1.0 - f))) * 255;
    if (i == 0)
            return (ft_create_rgb(hsv.v * 255, t, p));
    else if (i == 1)
            return (ft_create_rgb(q, hsv.v * 255, p));
    else if (i == 2)
            return (ft_create_rgb(p, hsv.v * 255, t));
    else if (i == 3)
            return (ft_create_rgb(p, q, hsv.v * 255));
    else if (i == 4)
            return (ft_create_rgb(t, p, hsv.v * 255));
    return (ft_create_rgb(hsv.v * 255, p, q));
}

int		ft_get_color_dist(t_window *infos, t_hsv color)
{
	int	ret;
    (void)infos;
	ret = ft_hsv2rgb(color);
	return (ret);
}

t_hsv	ft_rgb2hsv(t_color color)
{
    t_hsv         out;
    double      min;
	double		max;
	double		delta;

    min = color.r < color.g ? color.r : color.g;
    min = min  < color.b ? min  : color.b;
    max = color.r > color.g ? color.r : color.g;
    max = max  > color.b ? max  : color.b;
    out.v = max;
    delta = max - min;
    if (delta < 0.00001)
    {
        out.s = 0;
        out.h = 0; // undefined, maybe nan?
        return out;
    }
    if( max > 0.0 ) { // NOTE: if Max is == 0, this divide would cause a crash
        out.s = (delta / max);                  // s
    } else {
        // if max is 0, then r = g = b = 0
        // s = 0, h is undefined
        out.s = 0.0;
        out.h = 0;                            // its now undefined
        return out;
    }
    if( color.r >= max )                           // > is bogus, just keeps compilor happy
        out.h = ( color.g - color.b ) / delta;        // between yellow & magenta
    else
    if( color.g >= max )
        out.h = 2.0 + ( color.b - color.r ) / delta;  // between cyan & yellow
    else
        out.h = 4.0 + ( color.r - color.g ) / delta;  // between magenta & cyan

    out.h *= 60.0;                              // degrees

    if( out.h < 0.0 )
        out.h += 360.0;

    return out;
}

void	ft_bcolor(void *s, int color, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		((int *)s)[i] = color;
		i++;
	}
}

int		ft_lerp(int i, int color1, int color2, float nbp)
{
	t_color	c1;
	t_color	c2;
	t_color	c3;
	int		ret;

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
