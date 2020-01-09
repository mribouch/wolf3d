/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 14:50:40 by mribouch          #+#    #+#             */
/*   Updated: 2020/01/09 15:26:08 by mribouch         ###   ########.fr       */
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
	int	left_click;
	int	right_click;
	int	mouse_wheel_up;
	int	mouse_wheel_down;
}				t_key;

#endif