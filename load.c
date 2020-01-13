/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 19:04:40 by mribouch          #+#    #+#             */
/*   Updated: 2020/01/13 19:25:39 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		*ft_get_img_tex(int *tex, void *img_ptr)
{
	int	bpp;
	int	s_l;
	int	endian;

	tex = (int*)mlx_get_data_addr(img_ptr, &bpp, &s_l, &endian);
	return (tex);
}

void	ft_load_img_button_down(t_window *infos)
{
	infos->edit_button[0].button_down.img =
		ft_get_img_tex(infos->edit_button[0].button_down.img,
			infos->edit_button[0].button_down.img_ptr);
	infos->edit_button[1].button_down.img =
		ft_get_img_tex(infos->edit_button[1].button_down.img,
			infos->edit_button[1].button_down.img_ptr);
	infos->button[0].button_down.img =
		ft_get_img_tex(infos->button[0].button_down.img,
			infos->button[0].button_down.img_ptr);
	infos->button[1].button_down.img =
		ft_get_img_tex(infos->button[1].button_down.img,
			infos->button[1].button_down.img_ptr);
	infos->button[2].button_down.img =
		ft_get_img_tex(infos->button[2].button_down.img,
			infos->button[2].button_down.img_ptr);
	infos->button[3].button_down.img =
		ft_get_img_tex(infos->button[3].button_down.img,
			infos->button[3].button_down.img_ptr);
}

void	ft_load_img_button_up(t_window *infos)
{
	infos->edit_button[0].button_up.img =
		ft_get_img_tex(infos->edit_button[0].button_up.img,
			infos->edit_button[0].button_up.img_ptr);
	infos->edit_button[1].button_up.img =
		ft_get_img_tex(infos->edit_button[1].button_up.img,
			infos->edit_button[1].button_up.img_ptr);
	infos->button[0].button_up.img =
		ft_get_img_tex(infos->button[0].button_up.img,
			infos->button[0].button_up.img_ptr);
	infos->button[1].button_up.img =
		ft_get_img_tex(infos->button[1].button_up.img,
			infos->button[1].button_up.img_ptr);
	infos->button[2].button_up.img =
		ft_get_img_tex(infos->button[2].button_up.img,
			infos->button[2].button_up.img_ptr);
	infos->button[3].button_up.img =
		ft_get_img_tex(infos->button[3].button_up.img,
			infos->button[3].button_up.img_ptr);
}

void	ft_load_button_down(t_window *infos)
{
	infos->edit_button[0].button_down.img_ptr =
		mlx_xpm_file_to_image(infos->mlx_ptr, "button/yes_down.xpm",
			&infos->edit_button[0].button_down.w,
				&infos->edit_button[0].button_down.h);
	infos->edit_button[1].button_down.img_ptr =
		mlx_xpm_file_to_image(infos->mlx_ptr,
		"button/no_down.xpm", &infos->edit_button[1].button_down.w,
			&infos->edit_button[1].button_down.h);
	infos->button[0].button_down.img_ptr = mlx_xpm_file_to_image(infos->mlx_ptr,
		"button/play_down.xpm", &infos->button[0].button_down.w,
			&infos->button[0].button_down.h);
	infos->button[1].button_down.img_ptr = mlx_xpm_file_to_image(infos->mlx_ptr,
		"button/map_down.xpm", &infos->button[1].button_down.w,
			&infos->button[1].button_down.h);
	infos->button[2].button_down.img_ptr = mlx_xpm_file_to_image(infos->mlx_ptr,
		"button/edit_down.xpm", &infos->button[2].button_down.w,
			&infos->button[2].button_down.h);
	infos->button[3].button_down.img_ptr = mlx_xpm_file_to_image(infos->mlx_ptr,
		"button/quit_down.xpm", &infos->button[3].button_down.w,
			&infos->button[3].button_down.h);
}

void	ft_load_button_up(t_window *infos)
{
	infos->edit_button[0].button_up.img_ptr =
		mlx_xpm_file_to_image(infos->mlx_ptr,
			"button/yes_up.xpm", &infos->edit_button[0].button_up.w,
				&infos->edit_button[0].button_up.h);
	infos->edit_button[1].button_up.img_ptr =
		mlx_xpm_file_to_image(infos->mlx_ptr,
			"button/no_up.xpm", &infos->edit_button[1].button_up.w,
				&infos->edit_button[1].button_up.h);
	infos->button[0].button_up.img_ptr = mlx_xpm_file_to_image(infos->mlx_ptr,
		"button/play_up.xpm", &infos->button[0].button_up.w,
			&infos->button[0].button_up.h);
	infos->button[1].button_up.img_ptr = mlx_xpm_file_to_image(infos->mlx_ptr,
		"button/map_up.xpm", &infos->button[1].button_up.w,
			&infos->button[1].button_up.h);
	infos->button[2].button_up.img_ptr = mlx_xpm_file_to_image(infos->mlx_ptr,
		"button/edit_up.xpm", &infos->button[2].button_up.w,
			&infos->button[2].button_up.h);
	infos->button[3].button_up.img_ptr = mlx_xpm_file_to_image(infos->mlx_ptr,
		"button/quit_up.xpm", &infos->button[3].button_up.w,
			&infos->button[3].button_up.h);
}
