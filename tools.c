/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 16:40:19 by mribouch          #+#    #+#             */
/*   Updated: 2019/11/19 18:13:05 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#    include <stdio.h>
int		ft_get_lerp_tnt(t_window *infos, int color1, int color2, int nbp)
{
    t_color	c1;
    t_color	c2;
    t_color	c3;
    int		ret;

    if (infos->wolf.block_dist > 10)
    {
        return (0x000000);
    }
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

int		ft_get_lerp_dist(t_window *infos, int color1, int nbp)
{
    t_color	c1;
    double     perc;
    // t_color	c2;
    // t_color	c3;
    int		ret;
    (void)nbp;
    perc = 25;
	c1.r = (color1 & 0xFF0000) >> 16;
    c1.g = (color1 & 0x00FF00) >> 8;
    c1.b = (color1 & 0x0000FF);
    // c2.r = 127;
    // c2.g = 127;
    // c2.b = 127;
    if (infos->wolf.select_block == 8)
        perc = 5;
    // c1.r = (1 - perc) * c1.r + perc * c2.r;
    // c1.g = (1 - perc) * c1.g + perc * c2.g;
    // c1.b = (1 - perc) * c1.b + perc * c2.b;
    c1.r -= c1.r * (infos->wolf.block_dist * perc) / 100;
    c1.g -= c1.g * (infos->wolf.block_dist * perc) / 100;
    c1.b -= c1.b * (infos->wolf.block_dist * perc) / 100;
    ret = (c1.b << 0) | (c1.g << 8) | (c1.r << 16);
    if (ret < 0x000000)
			ret = 0x000000;
    // printf("color = %X\n", ret);
    return (ret);
}