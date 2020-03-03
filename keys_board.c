/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_board.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 14:55:24 by mribouch          #+#    #+#             */
/*   Updated: 2020/03/03 15:06:03 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		ft_close_window(t_window *infos)
{
	ft_quit_wolf(infos);
	exit(0);
	return (1);
}

void	ft_fill_key(t_window *infos)
{
	infos->keys.s = 0;
	infos->keys.w = 0;
	infos->keys.a = 0;
	infos->keys.d = 0;
	infos->keys.q = 0;
	infos->keys.e = 0;
}

int		ft_dealkey_press(int keycode, t_window *infos)
{
	if (keycode == 53)
	{
		if (infos->edit_menu == 1)
			infos->save_map = 1;
		else
		{
			ft_quit_wolf(infos);
			exit(0);
		}
	}
	if (keycode == 0)
		infos->keys.a = 1;
	if (keycode == 2)
		infos->keys.d = 1;
	if (keycode == 13)
		infos->keys.w = 1;
	if (keycode == 1)
		infos->keys.s = 1;
	if (keycode == 12)
		infos->keys.q = 1;
	if (keycode == 14)
		infos->keys.e = 1;
	return (1);
}

int		ft_dealk_release(int keycode, t_window *infos)
{
	if (keycode == 0)
		infos->keys.a = 0;
	if (keycode == 2)
		infos->keys.d = 0;
	if (keycode == 13)
		infos->keys.w = 0;
	if (keycode == 1)
		infos->keys.s = 0;
	if (keycode == 12)
		infos->keys.q = 0;
	if (keycode == 14)
		infos->keys.e = 0;
	return (1);
}
