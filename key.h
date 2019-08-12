/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 14:50:40 by mribouch          #+#    #+#             */
/*   Updated: 2019/06/26 15:08:03 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_H
# define KEY_H
# include "wolf.h"
# include "callbacks.h"

typedef struct	s_key
{
	int	r_arr;
	int	l_arr;
	int	up_arr;
	int	dwn_arr;
}				t_key;

// void	ft_fill_key(t_window *infos);
// int		ft_dealkey_press(int keycode, t_window *infos);

#endif