/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 17:22:54 by mribouch          #+#    #+#             */
/*   Updated: 2019/11/12 16:15:48 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

#   include <stdio.h>
# include <dirent.h>

void	ft_print_rd_bt(t_window *infos)
{
	int	i;
	t_coord2d coord;

	i = 0;
	while (i < infos->nb_rd_button)
	{
		coord.x = infos->rd_button[i].x;
		coord.y = infos->rd_button[i].y;
		// printf("x = %f, y = %f\n", coord.x, coord.y);
		ft_fullcircle(infos, coord, 8, 0xFFFFFF);
		if (infos->rd_button[i].checked == 1)
			ft_fullcircle(infos, coord, 5, 0x000000);
		i++;
	}
	// struct dirent *de;
	// DIR *dr;
	// int	count;
	// int	y;
	// t_coord2d	coord;

	// (void)infos;
	// count = 0;
	// y = 10;
	// coord.x = 20;
	// coord.y = 20;
	// dr = opendir("maps");
    // if (dr == NULL)
    // {
    //     printf("Could not open current directory");
    //     return ;
    // }
	// while ((de = readdir(dr)) != NULL)
	// {
	// 	count ++;
	// 	if (count > 2)
	// 	{
	// 		// ft_putendl(infos->map.name);
	// 		mlx_string_put(infos->mlx_ptr, infos->win_ptr, 40, y, 0xFFFFFF, de->d_name);
	// 		ft_fullcircle(infos, coord, 10, 0xFFFFFF);
	// 		if (ft_strcmp(ft_strjoin("maps/", de->d_name), infos->map.name) == 0)
	// 			ft_fullcircle(infos, coord, 5, 0x000000);
	// 		coord.y += 30;
	// 		y += 30;
	// 	}
	// }
	// count -= 2;
	// // printf("there is %d maps.\n", count);
    // closedir(dr);
	// // mlx_put_image_to_window(infos->mlx_ptr, infos->win_ptr, infos->game.img_ptr, 0, 0);
}

static void	ft_save(t_window *infos)
{
	int	fd;
	int	i;
	int	j;
	char	*line;

	if (!(line = malloc(sizeof(char) * (infos->map.width * 2 - 2))))
		return ;
	i = 0;
	j = 0;
	fd = open(infos->map.name, O_WRONLY);
	while (i < infos->map.height)
	{
		while (j < infos->map.width)
		{
			line[j] = *ft_itoa(infos->map.map[i][j]);
			ft_putchar_fd(line[j], fd);
			if (j < infos->map.width - 1)
				ft_putchar_fd(' ', fd);
			j++;
		}
		if (i < infos->map.height - 1)
		ft_putchar_fd('\n', fd);
		j = 0;
		i++;
	}
	close(fd);
}

void	ft_save_world(t_window *infos)
{
	char	answer[4];
	(void)infos;
	// ft_putendl("ahahah ou ais salut uais");
	while (ft_strcmp(answer, "n") != 0 && ft_strcmp(answer, "y") != 0)
	{
		ft_putendl("Do you want to save the map ? (y / n)");
		scanf("%s", answer);
	}
	if (ft_strcmp(answer, "y") == 0)
	{
		ft_putstr("you've saved the map : ");
		ft_putendl(infos->map.name);
	}
		ft_save(infos);
}

void	ft_edit(t_window *infos)
{
	infos->edit_menu = 1;
	infos->wolf.menu = 0;
}