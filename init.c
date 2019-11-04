/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 17:58:11 by mribouch          #+#    #+#             */
/*   Updated: 2019/10/31 15:17:20 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

#include <stdio.h>

#include <math.h>

static int		*ft_get_img_tex(int	*tex, void *img_ptr)
{
	int	bpp;
	int	s_l;
	int	endian;

	tex = (int*)mlx_get_data_addr(img_ptr, &bpp, &s_l, &endian);
	// ft_bzero(infos->img, infos->width * infos->height);
	return (tex);
}

void	ft_load_texture(t_window *infos)
{
	int		i;
	int		fd;
	char	*line;
	int		size;
	char	*path;

	fd = open("textures.txt", O_RDONLY);
	i = 0;
	if (get_next_line(fd, &line) <= 0)
		return ;
	size = ft_atoi(line);
	infos->nb_tex_tb = size;
	free(line);
	if (!(infos->texture = malloc(sizeof(t_image) * (size))))
		return ;
	while (get_next_line(fd, &line) > 0)
	{
		path = ft_strjoin("textures/", line);
		infos->texture[i].img_ptr = mlx_xpm_file_to_image( infos->mlx_ptr, path, &infos->texture[i].w, &infos->texture[i].h );
		free(line);
		free(path);
		i++;
	}
	i = 0;
	while (i < size)
	{
		infos->texture[i].img = ft_get_img_tex(infos->texture[i].img, infos->texture[i].img_ptr);
		i++;
	}
	close(fd);
}

void	ft_init_wolf(t_window *infos)
{
	double	camx;

	camx = 2 * (WIDTH / 2) / (double)infos->width - 1;
	if (!(infos->wolf.tab_ray = malloc(sizeof(t_ray) * (WIDTH))))
		return ;
	// infos->wolf.angle_cam = 0.349066;
	// infos->wolf.angle_cam = 0.0;
	// infos->wolf.d_camscreen = (WIDTH / 2) / tan(FOV / 2);
	ft_load_texture(infos);
	if (!(infos->gui = malloc(sizeof(t_image) * (3))))
		return ;
	infos->gui[0].img_ptr = mlx_xpm_file_to_image( infos->mlx_ptr, "gui.xpm", &infos->gui[0].w, &infos->gui[0].h );
	infos->gui[0].img = ft_get_img_tex(infos->gui[0].img, infos->gui[0].img_ptr);
	infos->gui[1].img_ptr = mlx_xpm_file_to_image( infos->mlx_ptr, "gui_select.xpm", &infos->gui[1].w, &infos->gui[1].h );
	infos->gui[1].img = ft_get_img_tex(infos->gui[1].img, infos->gui[1].img_ptr);
	infos->gui[2].img_ptr = mlx_xpm_file_to_image( infos->mlx_ptr, "Briquet.xpm", &infos->gui[2].w, &infos->gui[2].h );
	infos->gui[2].img = ft_get_img_tex(infos->gui[2].img, infos->gui[2].img_ptr);
	infos->wolf.editor = 0;
	infos->wolf.explode = 0;
	infos->wolf.exp_iter = 0;
	infos->wolf.select_block = 0;
	infos->wolf.edit_distance_wall = 3;
	infos->wolf.plane.x = 0;
	infos->wolf.plane.y = 0.66;
	infos->wolf.pos_cam.x = 10;
	infos->wolf.pos_cam.y = 8;
	infos->wolf.dir_cam.x = -1;
	infos->wolf.dir_cam.y = 0;
	infos->wolf.dir_cam.color = 0x00FF00;
	infos->map.map_pos.x = 0;
	infos->map.map_pos.y = 0;
	infos->wolf.old_block.x = (int)(infos->wolf.pos_cam.x + infos->wolf.dir_cam.x * 3 + infos->wolf.plane.x * camx);
	infos->wolf.old_block.y = (int)(infos->wolf.pos_cam.y + infos->wolf.dir_cam.y * 3 + infos->wolf.plane.y * camx);
	infos->wolf.old_block.color = 0;
	// infos->map.map[(int)infos->wolf.old_block.y][(int)infos->wolf.old_block.y] = 1;
	printf("address = %p\n", &infos->wolf.tab_ray);
}