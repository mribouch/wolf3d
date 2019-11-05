/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 14:55:24 by mribouch          #+#    #+#             */
/*   Updated: 2019/11/05 13:57:23 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "key.h"
#include "callbacks.h"

int                     ft_get_cursor(int x, int y, t_window *infos)
{
        infos->cursor.x = x;
        infos->cursor.y = y;
        return (0);
}

void	ft_fill_key(t_window *infos)
{
	infos->keys.s = 0;
	infos->keys.w = 0;
	infos->keys.a = 0;
	infos->keys.d = 0;
	infos->keys.q = 0;
	infos->keys.e = 0;
	infos->keys.i = 0;
	infos->keys.o = 0;
	infos->keys.f = 0;
}

int		ft_dealkey_press(int keycode, t_window *infos)
{
	(void)infos;
	ft_putnbr(keycode);
	ft_putchar('\n');
	if (keycode == 53)
		exit(0);
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
	if (keycode == 34)
		infos->keys.i = 1;
	if (keycode == 31)
		infos->keys.o = 1;
	if (keycode == 257)
		infos->keys.f = 1;
	ft_callback(infos);
	return (1);
}

int		ft_dealk_release(int keycode, t_window *infos)
{
	// ft_bzero(infos->img, WIDTH * HEIGHT);
	ft_putnbr(keycode);
	ft_putchar('\n');
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
	if (keycode == 34)
		infos->keys.i = 0;
	if (keycode == 31)
		infos->keys.o = 0;
	if (keycode == 257)
		infos->keys.f = 0;
	ft_callback(infos);
	return (1);
}

int	ft_button_press(int button, int x, int y, t_window *infos)
{
	(void)x;
	(void)y;

	// ft_putendl("press");
	// ft_putnbr(button);
	// ft_putchar('\n');

	if (button == 1)
		infos->keys.left_click = 1;
	if (button == 2)
		infos->keys.right_click = 1;
	if (button == 5)
		infos->keys.mouse_wheel_up = 1;
	if (button == 4)
		infos->keys.mouse_wheel_down = 1;
	return (0);
}

int	ft_button_release(int button, int x, int y, t_window *infos)
{
	(void)x;
	(void)y;
	// ft_putendl("release");
	// ft_putnbr(button);
	// ft_putchar('\n');
	if (button == 1)
		infos->keys.left_click = 0;
	if (button == 2)
		infos->keys.right_click = 0;
	return (0);
}