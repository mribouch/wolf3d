/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 15:57:45 by mribouch          #+#    #+#             */
/*   Updated: 2019/04/10 11:38:54 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_set_color(int key, t_window *infos)
{
	if (key == 8)
	{
		infos->colid++;
		if (infos->colid > 5)
			infos->colid = 0;
		if (infos->colid == 0)
			infos->bcol = 0x000000;
		if (infos->colid == 1)
			infos->bcol = 0x003B3E;
		if (infos->colid == 2)
			infos->bcol = 0x0A3E00;
		if (infos->colid == 3)
			infos->bcol = 0x3C003E;
		if (infos->colid == 4)
			infos->bcol = 0x542E00;
		if (infos->colid == 5)
			infos->bcol = 0x540000;
		ft_bcolor(infos->img, infos->bcol, (infos->height * infos->width));
		ft_callback(infos);
	}
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
