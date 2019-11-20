/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:11:08 by mribouch          #+#    #+#             */
/*   Updated: 2019/11/19 14:32:01 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

#include <math.h>

#include <stdio.h>

// static void	ft_print_map(t_window *infos)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (infos->map.map[j] != NULL)
// 		{
// 			while (i < infos->map.width)
// 			{
// 				printf("%d ", infos->map.map[j][i]);
// 				i++;
// 			}
// 			printf("\n");
// 			i = 0;
// 			j++;
// 		}
// }

int		ft_callback(t_window *infos)
{
	ft_bzero(infos->game.img, sizeof(int) * (WIDTH * HEIGHT));
	if (infos->wolf.menu == 0)
		ft_dealk_act(infos);
	ft_update(infos);
	ft_draw(infos);
	return (1);
}

int		*ft_get_img(t_image image)
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
	infos->menu.h = HEIGHT;
	infos->menu.w = WIDTH;
	infos->win_ptr = mlx_new_window(infos->mlx_ptr, WIDTH, HEIGHT, "Wolf3d");
	infos->game.img = NULL;
	infos->menu.img = NULL;
	infos->game.img_ptr = mlx_new_image(infos->mlx_ptr, WIDTH, HEIGHT);
	infos->menu.img_ptr = mlx_new_image(infos->mlx_ptr, WIDTH, HEIGHT);
	infos->test.x = 10;
	infos->test.y = 20;
	infos->game.img = ft_get_img(infos->game);
	infos->menu.img = ft_get_img(infos->game);
	return (infos);
}

int	main(int ac, char **av)
{
	t_window	*infos;
	int			fd;

	if (ac != 2)
		ft_putendl("usage: ./wolf3d FileName");
	else
	{
		if (!(infos = malloc(sizeof(t_window))))
			return (0);
		int	x;
		int	y;

		x = 16;
		y = 16;
		infos = ft_fill_infos(infos);
		fd = open(av[1], O_RDONLY);
		// infos->brick_img_ptr = mlx_xpm_file_to_image( infos->mlx_ptr, "brick-_1_.xpm", &x, &y );
		// infos->img_brick = ft_get_img_brick(infos);
		// printf("couleuuuuuuur = %x\n", infos->img_brick[15]);
		ft_putendl(av[1]);
		infos->map.name = av[1];
		if ((infos->map.map = ft_get_map(fd, infos)) == 0)
		{
			ft_putendl("Wrong input ! The lines doesn't have the same lenght !");
			exit(0);
		}
		close(fd);
		// ft_print_map(infos);
		ft_init_wolf(infos);
		// mlx_hook(infos->win_ptr, 5, (1L << 3), ft_check_button, infos);
		// infos->previous = clock();
		// infos->lag = 0.0;
		mlx_hook(infos->win_ptr, MOTION_NOTIFY, POINTER_MOTION_MASK, ft_get_cursor, infos);
		mlx_hook(infos->win_ptr, BUTTON_PRESS, BUTTON_PRESS_MASK, ft_button_press, infos);
		mlx_hook(infos->win_ptr, BUTTON_RELEASE, BUTTON_RELEASE_MASK, ft_button_release, infos);
		mlx_hook(infos->win_ptr, KEY_PRESS, KEY_PRESS_MASK, ft_dealkey_press, infos);
		mlx_hook(infos->win_ptr, KEY_RELEASE, KEY_RELEASE_MASK, ft_dealk_release, infos);
		mlx_loop_hook(infos->mlx_ptr, ft_callback, infos);
		mlx_loop(infos->mlx_ptr);
	}
	return (0);
}