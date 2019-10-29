/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 16:40:19 by mribouch          #+#    #+#             */
/*   Updated: 2019/10/29 18:07:03 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		ft_get_tnt_color(t_window *infos, int color)
{
    t_color	c1;
    t_color	c2;
    t_color	c3;
    int		ret;
	c1.r = (color & 0xFF0000) >> 16;
    c1.g = (color & 0x00FF00) >> 8;
    c1.b = (color & 0x0000FF);
    c2.r = (0xFFFFFF & 0xFF0000) >> 16;
    c2.g = (0xFFFFFF & 0x00FF00) >> 8;
    c2.b = (0xFFFFFF & 0x0000FF);
    c3.r = c1.r + (c2.r - c1.r) * (infos->wolf.exp_iter - 0) / (100 - 0);
    c3.g = c1.g + (c2.g - c1.g) * (infos->wolf.exp_iter - 0) / (100 - 0);
    c3.b = c1.b + (c2.b - c1.b) * (infos->wolf.exp_iter - 0) / (100 - 0);
    ret = (c3.b << 0) | (c3.g << 8) | (c3.r << 16);
    return (ret);
}

int		ft_create_rgb(t_color color)
{
        int     ret;

        ret = ((int)color.b << 0) | ((int)color.g << 8) | ((int)color.r << 16);
        return (ret);
}

t_color	ft_int_to_rgb(int color)
{
	t_color	ret;

	ret.r = (color & 0xFF0000) >> 16;
    ret.g = (color & 0x00FF00) >> 8;
    ret.b = (color & 0x0000FF);
	return (ret);
}

int		ft_negative_col(t_color color)
{
	color.r = 255 - color.r;
	color.g = 255 - color.g;
	color.b = 255 - color.b;
	return (ft_create_rgb(color));
}