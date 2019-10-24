/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 14:50:40 by mribouch          #+#    #+#             */
/*   Updated: 2019/10/23 17:07:54 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_H
# define KEY_H
# include "wolf.h"
# include "callbacks.h"

typedef struct	s_key
{
	int	d;
	int	a;
	int	w;
	int	s;
	int	q;
	int	e;
	int	i;
	int	o;
	int	left_click;
	int	right_click;
	int	mouse_wheel_up;
	int	mouse_wheel_down;
}				t_key;

// void	ft_fill_key(t_window *infos);
// int		ft_dealkey_press(int keycode, t_window *infos);

#endif