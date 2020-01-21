/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 16:40:19 by mribouch          #+#    #+#             */
/*   Updated: 2020/01/21 17:54:27 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		ft_spawn_cam(t_window *infos)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < infos->map.height)
	{
		while (j < infos->map.width)
		{
			if (infos->map.map[i][j] == 0)
			{
				infos->wolf.pos_cam.x = j + 0.5;
				infos->wolf.pos_cam.y = i + 0.5;
				return (1);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

int		ft_get_lerp_tnt(t_window *infos, int color1, int color2, int nbp)
{
	t_color	c1;
	t_color	c2;
	t_color	c3;
	int		ret;

	if (infos->wolf.block_dist > 10)
		return (0x000000);
	c1.r = (color1 & 0xFF0000) >> 16;
	c1.g = (color1 & 0x00FF00) >> 8;
	c1.b = (color1 & 0x0000FF);
	c2.r = (color2 & 0xFF0000) >> 16;
	c2.g = (color2 & 0x00FF00) >> 8;
	c2.b = (color2 & 0x0000FF);
	c3.r = c1.r + (c2.r - c1.r) * (infos->wolf.exp_iter - 0) / (nbp - 0);
	c3.g = c1.g + (c2.g - c1.g) * (infos->wolf.exp_iter - 0) / (nbp - 0);
	c3.b = c1.b + (c2.b - c1.b) * (infos->wolf.exp_iter - 0) / (nbp - 0);
	ret = (c3.b << 0) | (c3.g << 8) | (c3.r << 16);
	return (ret);
}

int		ft_get_lerp_dist(t_window *infos, int color1, float dist, float nbp)
{
	t_color	c1;
	t_color	tmp;
	double	perc;
	int		ret;

	dist /= 2;
	perc = nbp;
	c1.r = (color1 & 0xFF0000) >> 16;
	c1.g = (color1 & 0x00FF00) >> 8;
	c1.b = (color1 & 0x0000FF);
	if (infos->wolf.select_block == 8)
		perc = 1;
	tmp.r = c1.r / (dist * perc);
	if (tmp.r >= 0 && tmp.r <= c1.r)
		c1.r = tmp.r;
	tmp.g = c1.g / (dist * perc);
	if (tmp.g >= 0 && tmp.g <= c1.g)
		c1.g = tmp.g;
	tmp.b = c1.b / (dist * perc);
	if (tmp.b >= 0 && tmp.b <= c1.b)
		c1.b = tmp.b;
	ret = (c1.b << 0) | (c1.g << 8) | (c1.r << 16);
	if (ret < 0x000000)
		ret = 0x000000;
	return (ret);
}
