/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tnt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 14:28:06 by mribouch          #+#    #+#             */
/*   Updated: 2020/01/08 14:29:44 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	ft_destroy_block(t_window *infos, int x, int y)
{
	if (y + 1 < infos->map.height - 1)
		infos->map.map[y + 1][x] = 0;
	if (y - 1 >= 1)
		infos->map.map[y - 1][x] = 0;
	if (x + 1 < infos->map.width - 1)
		infos->map.map[y][x + 1] = 0;
	if (x - 1 >= 1)
		infos->map.map[y][x - 1] = 0;
	if (y - 1 >= 1 && x - 1 >= 1)
		infos->map.map[y - 1][x - 1] = 0;
	if (y + 1 < infos->map.height - 1 && x + 1 < infos->map.width - 1)
		infos->map.map[y + 1][x + 1] = 0;
	if (y - 1 >= 1 && x + 1 < infos->map.width - 1)
		infos->map.map[y - 1][x + 1] = 0;
	if (y + 1 < infos->map.height - 1 && x - 1 >= 1)
		infos->map.map[y + 1][x - 1] = 0;
}

static void	ft_explode(t_window *infos, int x, int y)
{
	infos->map.map[y][x] = 0;
	if (infos->map.map[y][x + 1] == 6)
		ft_explode(infos, x + 1, y);
	if (infos->map.map[y][x - 1] == 6)
		ft_explode(infos, x - 1, y);
	if (infos->map.map[y + 1][x] == 6)
		ft_explode(infos, x, y + 1);
	if (infos->map.map[y - 1][x] == 6)
		ft_explode(infos, x, y - 1);
	if (infos->map.map[y + 1][x + 1] == 6)
		ft_explode(infos, x + 1, y + 1);
	if (infos->map.map[y - 1][x - 1] == 6)
		ft_explode(infos, x - 1, y - 1);
	if (infos->map.map[y + 1][x - 1] == 6)
		ft_explode(infos, x - 1, y + 1);
	if (infos->map.map[y - 1][x + 1] == 6)
		ft_explode(infos, x + 1, y - 1);
	ft_destroy_block(infos, x, y);
}

void	ft_explode_tnt(t_window *infos)
{
	int	x;
	int	y;
	infos->wolf.exp_iter ++;
	if (infos->wolf.exp_iter == 100)
	{
		x = infos->wolf.tnt_block.x;
		y = infos->wolf.tnt_block.y;
		ft_explode(infos, x, y);
		infos->wolf.explode = 0;
		infos->wolf.exp_iter = 0;
	}
}