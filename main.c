/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:11:08 by mribouch          #+#    #+#             */
/*   Updated: 2020/01/07 19:36:15 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

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
	// int	i;

	// i = 0;
	// ft_putendl("avant le bzero");
	ft_bzero(infos->game.img, sizeof(int) * (WIDTH * HEIGHT));
	// ft_putendl("avant le dealk act");
	if (infos->wolf.menu == 0)
		ft_dealk_act(infos);
	// ft_putendl("avant update");
	ft_update(infos);
	// ft_putendl("avant draw");
	// while (i < WIDTH)
	// {
	// 	pthread_join(infos->col_th[i], NULL);
	// 	i++;
	// }
	ft_draw(infos);
	// ft_putendl("apres draw");
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
	infos->win_ptr = mlx_new_window(infos->mlx_ptr, WIDTH, HEIGHT, "Wolf3d");
	infos->game.img = NULL;
	infos->game.img_ptr = mlx_new_image(infos->mlx_ptr, WIDTH, HEIGHT);
	infos->game.img = ft_get_img(infos->game);
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
		fd = open(av[1], O_RDONLY);
		infos->map.name = av[1];
		if ((infos->map.map = ft_get_map(fd, infos)) == 0)
		{
			ft_putendl("Wrong input ! The lines doesn't have the same lenght !");
			ft_putendl("ON ets bien la ?");
			close(fd);
			free(infos);
			while(1);
			exit(0);
		}
		infos = ft_fill_infos(infos);
		close(fd);
		ft_init_wolf(infos);
		mlx_hook(infos->win_ptr, MOTION_NOTIFY, POINTER_MOTION_MASK, ft_get_cursor, infos);
		mlx_hook(infos->win_ptr, BUTTON_PRESS, BUTTON_PRESS_MASK, ft_button_press, infos);
		mlx_hook(infos->win_ptr, BUTTON_RELEASE, BUTTON_RELEASE_MASK, ft_button_release, infos);
		mlx_hook(infos->win_ptr, KEY_PRESS, KEY_PRESS_MASK, ft_dealkey_press, infos);
		mlx_hook(infos->win_ptr, KEY_RELEASE, KEY_RELEASE_MASK, ft_dealk_release, infos);
		mlx_hook(infos->win_ptr, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK, ft_close_window, infos);
		mlx_loop_hook(infos->mlx_ptr, ft_callback, infos);
		mlx_loop(infos->mlx_ptr);
	}
	return (0);
}