/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 07:45:20 by mribouch          #+#    #+#             */
/*   Updated: 2020/01/09 15:48:47 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	ft_quit_wrong_map(t_window *infos, int fd)
{
	close(fd);
	ft_putendl("Wrong format file !");
	ft_free_rd_button(infos);
	ft_free_button(infos);
	ft_free_texture(infos);
	mlx_destroy_image(infos->mlx_ptr, infos->game.img_ptr);
	mlx_destroy_window(infos->mlx_ptr, infos->win_ptr);
	free(infos);
	exit(0);
}

void		ft_check_map(t_window *infos)
{
	int		i;
	char	*map;
	int		fd;

	i = 0;
	while (i < infos->nb_rd_button)
	{
		if (infos->rd_button[i].checked == 1)
		{
			map = ft_strjoin("maps/", infos->rd_button[i].data);
			if (ft_strcmp(map, infos->map.name) != 0)
			{
				fd = open(map, O_RDONLY);
				ft_free_map(infos);
				infos->map.name = map;
				if ((infos->map.map = ft_get_map(fd, infos)) == 0)
					ft_quit_wrong_map(infos, fd);
				close(fd);
			}
			free(map);
		}
		i++;
	}
}
