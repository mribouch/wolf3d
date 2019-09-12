/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 14:55:24 by mribouch          #+#    #+#             */
/*   Updated: 2019/08/12 16:34:18 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "key.h"
#include "callbacks.h"

void	ft_fill_key(t_window *infos)
{
	infos->keys.dwn_arr = 0;
	infos->keys.up_arr = 0;
	infos->keys.l_arr = 0;
	infos->keys.r_arr = 0;
}

int		ft_dealkey_press(int keycode, t_window *infos)
{
	(void)infos;
	// ft_putnbr(keycode);
	// ft_putchar('\n');
	// ft_bzero(infos->img, WIDTH * HEIGHT);
	if (keycode == 53)
		exit(0);
	if (keycode == 123)
		infos->keys.l_arr = 1;
	if (keycode == 124)
		infos->keys.r_arr = 1;
	if (keycode == 126)
		infos->keys.up_arr = 1;
	if (keycode == 125)
		infos->keys.dwn_arr = 1;
	ft_callback(infos);
	return (1);
}

int		ft_dealk_release(int keycode, t_window *infos)
{
	// ft_bzero(infos->img, WIDTH * HEIGHT);
	if (keycode == 123)
		infos->keys.l_arr = 0;
	if (keycode == 124)
		infos->keys.r_arr = 0;
	if (keycode == 126)
		infos->keys.up_arr = 0;
	if (keycode == 125)
		infos->keys.dwn_arr = 0;
	ft_callback(infos);
	return (1);
}