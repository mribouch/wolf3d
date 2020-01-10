/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 16:36:51 by mribouch          #+#    #+#             */
/*   Updated: 2020/01/10 17:15:34 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void				ft_button_yn_in_game(t_window *infos, int id,
	t_image up_down)
{
	int	i;
	int	j;
	int	a;
	int	b;

	i = infos->edit_button[id].y;
	j = infos->edit_button[id].x;
	a = 0;
	b = 0;
	while (i < infos->edit_button[id].y + infos->edit_button[id].button_up.h)
	{
		while (j < infos->edit_button[id].x +
			infos->edit_button[id].button_up.w)
		{
			infos->game.img[j + i * WIDTH] = up_down.img[a + b *
				infos->edit_button[id].button_up.w];
			j++;
			a++;
		}
		j = infos->edit_button[id].x;
		a = 0;
		i++;
		b++;
	}
}

void				ft_button_in_game(t_window *infos, int id, t_image up_down)
{
	int	i;
	int	j;
	int	a;
	int	b;

	i = infos->button[id].y;
	j = infos->button[id].x;
	a = 0;
	b = 0;
	while (i < infos->button[id].y + infos->button[id].button_up.h)
	{
		while (j < infos->button[id].x + infos->button[id].button_up.w)
		{
			infos->game.img[j + i * WIDTH] =
				up_down.img[a + b * infos->button[id].button_up.w];
			j++;
			a++;
		}
		j = infos->button[id].x;
		a = 0;
		i++;
		b++;
	}
}

static t_image		ft_iter_tmpcoef(t_putimage it, t_image print, t_image main)
{
	it.tmpitcoef--;
	if (print.img[(int)(it.iter.x + it.iter.y *
		print.w)] >= 0x000000)
		main.img[(int)(it.tmp.x + it.itcoef + (it.tmp.y +
			it.tmpitcoef) * WIDTH)] = print.img[(int)
				(it.iter.x + it.iter.y * print.w)];
	return (main);
}

static t_putimage	ft_init_img_in_game(t_putimage it, t_coord2d coord)
{
	it.tmp.y = coord.y;
	it.tmp.x = coord.x;
	it.iter.x = 0;
	it.iter.y = 0;
	it.itcoef = -1;
	it.tmpcoef = 0;
	it.tmpitcoef = 0;
	return (it);
}

void				ft_img_in_game(t_image main, t_image print,
	t_coord2d coord, int coef)
{
	t_putimage	it;

	it.itcoef = 0;
	it = ft_init_img_in_game(it, coord);
	while (it.tmp.y < coord.y + (print.h * coef))
	{
		while (it.tmp.x < (coord.x + print.w * coef))
		{
			while (++it.itcoef < coef + 1)
			{
				while (it.tmpitcoef++ < coef)
					main = ft_iter_tmpcoef(it, print, main);
				it.tmpitcoef = 0;
			}
			it.itcoef = 0;
			it.tmp.x += coef;
			it.iter.x++;
		}
		it.tmp.x = coord.x;
		it.iter.x = 0;
		it.tmp.y += coef;
		it.iter.y++;
	}
}
