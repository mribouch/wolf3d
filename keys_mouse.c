/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 15:11:24 by mribouch          #+#    #+#             */
/*   Updated: 2020/01/09 15:29:30 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int	ft_get_cursor(int x, int y, t_window *infos)
{
	infos->cursor.x = x;
	infos->cursor.y = y;
	return (0);
}

int	ft_button_press(int button, int x, int y, t_window *infos)
{
	(void)x;
	(void)y;
	ft_putnbr(button);
	ft_putchar('\n');
	if (button == 1)
		infos->keys.left_click = 1;
	if (button == 3)
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
	if (button == 1)
		infos->keys.left_click = 0;
	if (button == 3)
		infos->keys.right_click = 0;
	return (0);
}
