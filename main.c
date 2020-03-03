/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:11:08 by mribouch          #+#    #+#             */
/*   Updated: 2020/03/03 15:06:11 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int			ft_callback(t_window *infos)
{
	ft_bzero(infos->game.img, sizeof(int) * (WIDTH * HEIGHT));
	if (infos->wolf.menu == 0)
		ft_dealk_act(infos);
	ft_update(infos);
	ft_draw(infos);
	return (1);
}

int			*ft_get_img(t_image image)
{
	int	bpp;
	int	s_l;
	int	endian;

	image.img = (int*)mlx_get_data_addr(image.img_ptr, &bpp, &s_l, &endian);
	ft_bzero(image.img, image.w * image.h);
	return (image.img);
}

t_window	*ft_fill_infos(t_window *infos)
{
	infos->mlx_ptr = mlx_init();
	infos->game.h = HEIGHT;
	infos->game.w = WIDTH;
	infos->win_ptr = mlx_new_window(infos->mlx_ptr, WIDTH, HEIGHT, "Wolf3d");
	infos->game.img = NULL;
	infos->game.img_ptr = mlx_new_image(infos->mlx_ptr, WIDTH, HEIGHT);
	infos->game.img = ft_get_img(infos->game);
	return (infos);
}

static void	ft_loop_hook(t_window *infos)
{
	mlx_hook(infos->win_ptr, MOTION_NOTIFY, (1L << 6), ft_get_cursor, infos);
	mlx_hook(infos->win_ptr, BUTTON_PRESS, (1L << 2), ft_button_press, infos);
	mlx_hook(infos->win_ptr, BUTTON_RELEASE, (1L << 3),
		ft_button_release, infos);
	mlx_hook(infos->win_ptr, KEY_PRESS, (1L << 0), ft_dealkey_press, infos);
	mlx_hook(infos->win_ptr, KEY_RELEASE, (1L << 1), ft_dealk_release, infos);
	mlx_hook(infos->win_ptr, DESTROY_NOTIFY, (1L << 17),
		ft_close_window, infos);
	mlx_loop_hook(infos->mlx_ptr, ft_callback, infos);
	mlx_loop(infos->mlx_ptr);
}

int			main(int ac, char **av)
{
	t_window	*infos;
	int			fd;

	if (ac != 2)
		ft_putendl("usage: ./wolf3d FileName");
	else
	{
		if (!(infos = malloc(sizeof(t_window))))
			return (0);
		fd = open(av[1], O_RDONLY);
		infos->map.name = av[1];
		if ((infos->map.map = ft_get_map(fd, infos)) == 0)
		{
			ft_putendl("Wrong format file !");
			close(fd);
			free(infos);
			exit(0);
		}
		infos = ft_fill_infos(infos);
		close(fd);
		ft_init_wolf(infos);
		ft_loop_hook(infos);
	}
	return (0);
}
