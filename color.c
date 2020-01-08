/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 18:06:31 by mribouch          #+#    #+#             */
/*   Updated: 2020/01/08 15:17:33 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		ft_create_rgb(double r, double g, double b)
{
	int	ret;

	ret = ((int)b << 0) | ((int)g << 8) | ((int)r << 16);
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
	return (ft_create_rgb(color.r, color.g, color.b));
}
