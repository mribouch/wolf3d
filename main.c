/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:11:08 by mribouch          #+#    #+#             */
/*   Updated: 2019/09/09 12:16:14 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <math.h>

#include <stdio.h>

static void	ft_print_map(t_window *infos)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (infos->map.map[j] != NULL)
		{
			while (i < infos->map.width)
			{
				printf("%d ", infos->map.map[j][i]);
				i++;
			}
			printf("\n");
			i = 0;
			j++;
		}
}

int		ft_callback(t_window *infos)
{
	t_coord2d	pos_cam_mm;
	// ft_putendl("heysalut");
	ft_bzero(infos->img, sizeof(int) * (WIDTH * HEIGHT));
	pos_cam_mm.x = 100;
	pos_cam_mm.y = 100;
	if (infos->keys.l_arr == 1)
		infos->wolf.angle_cam -= 0.07;
	if (infos->keys.r_arr == 1)
		infos->wolf.angle_cam += 0.07;
	if (infos->keys.up_arr == 1)
	{
		infos->wolf.pos_cam.x += cos(infos->wolf.angle_cam);
		infos->wolf.pos_cam.y += sin(infos->wolf.angle_cam);
		infos->map.map_pos.x -= cos(infos->wolf.angle_cam);
		infos->map.map_pos.y -= sin(infos->wolf.angle_cam);
	}
	if (infos->keys.dwn_arr == 1)
	{
		infos->wolf.pos_cam.x -= cos(infos->wolf.angle_cam);
		infos->wolf.pos_cam.y -= sin(infos->wolf.angle_cam);
		infos->map.map_pos.x += cos(infos->wolf.angle_cam);
		infos->map.map_pos.y += sin(infos->wolf.angle_cam);
	}
	// infos->wolf.dir_cam.x = cos(infos->wolf.angle_cam) * 100 + infos->wolf.pos_cam.x;
	// infos->wolf.dir_cam.y = sin(infos->wolf.angle_cam) * 100 + infos->wolf.pos_cam.y;
	infos->wolf.dir_cam.x = cos(infos->wolf.angle_cam) * 100 + pos_cam_mm.x;
	infos->wolf.dir_cam.y = sin(infos->wolf.angle_cam) * 100 + pos_cam_mm.y;
	ft_update_ray(infos);
	// infos->wolf.dir_cam.x = cos(infos->wolf.angle_cam) * 50 + infos->map.map_pos.x;
	// infos->wolf.dir_cam.y = sin(infos->wolf.angle_cam) * 50 + infos->map.map_pos.y;
	ft_draw_wolf(infos);
	ft_draw_minimap(infos, infos->map.map_pos);
	ft_draw_ray(infos);
	infos->wolf.dir_cam.color = 0xFF0000;
	ft_line_new(infos, pos_cam_mm, infos->wolf.dir_cam);
	ft_draw_cam(infos);
	// infos->img[(int)infos->wolf.pos_cam.x + (int)infos->wolf.pos_cam.y * WIDTH] = 0xFFFFFF;
	mlx_put_image_to_window(infos->mlx_ptr,
    	infos->win_ptr, infos->img_ptr, 0, 0);
	return (1);
}

int		*ft_get_img(t_window *infos)
{
	int	bpp;
	int	s_l;
	int	endian;

	infos->img = (int*)mlx_get_data_addr(infos->img_ptr, &bpp, &s_l, &endian);
	ft_bzero(infos->img, infos->width * infos->height);
	return (infos->img);
}

t_window	*ft_fill_infos(t_window *infos)
{
	infos->mlx_ptr = mlx_init();
	infos->height = HEIGHT;
	infos->width = WIDTH;
	infos->win_ptr = mlx_new_window(infos->mlx_ptr, WIDTH, HEIGHT, "Wolf3d");
	infos->img = NULL;
	infos->img_ptr = mlx_new_image(infos->mlx_ptr, WIDTH, HEIGHT);
	infos->test.x = 10;
	infos->test.y = 20;
	infos->img = ft_get_img(infos);
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
		infos = ft_fill_infos(infos);
		fd = open(av[1], O_RDONLY);

		ft_putendl(av[1]);
		if ((infos->map.map = ft_get_map(fd, infos)) == 0)
		{
			ft_putendl("Wrong input ! The lines doesn't have the same lenght !");
			exit(0);
		}
		ft_print_map(infos);
		ft_init_wolf(infos);
		// ft_putendl("avant hook press");
		mlx_hook(infos->win_ptr, KEY_PRESS, KEY_PRESS_MASK, ft_dealkey_press, infos);
		// ft_putendl("avant hook release");
		mlx_hook(infos->win_ptr, KEY_RELEASE, KEY_RELEASE_MASK, ft_dealk_release, infos);
		// ft_putendl("avant loophookCB");
		mlx_loop_hook(infos->mlx_ptr, ft_callback, infos);
		mlx_loop(infos->mlx_ptr);
	}
	return (0);
}