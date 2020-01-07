/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 17:58:11 by mribouch          #+#    #+#             */
/*   Updated: 2020/01/07 15:42:29 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static int		*ft_get_img_tex(int	*tex, void *img_ptr)
{
	int	bpp;
	int	s_l;
	int	endian;

	tex = (int*)mlx_get_data_addr(img_ptr, &bpp, &s_l, &endian);
	if (tex == NULL)
		ft_putendl("wowowowowowowow c'est quoi ca");
	// ft_bzero(infos->img, infos->width * infos->height);
	return (tex);
}

static void	ft_load_button(t_window *infos)
{
	if (!(infos->button = malloc(sizeof(t_button) * (5))))
		return ;
	if (!(infos->edit_button = malloc(sizeof(t_button) * 3)))
		return;
	infos->edit_button[0].button_up.img_ptr = mlx_xpm_file_to_image(infos->mlx_ptr,
		"button/yes_up.xpm", &infos->edit_button[0].button_up.w, &infos->edit_button[0].button_up.h);
	infos->edit_button[0].button_down.img_ptr = mlx_xpm_file_to_image(infos->mlx_ptr,
		"button/yes_down.xpm", &infos->edit_button[0].button_down.w, &infos->edit_button[0].button_down.h);
	infos->edit_button[1].button_up.img_ptr = mlx_xpm_file_to_image(infos->mlx_ptr,
		"button/no_up.xpm", &infos->edit_button[1].button_up.w, &infos->edit_button[1].button_up.h);
	infos->edit_button[1].button_down.img_ptr = mlx_xpm_file_to_image(infos->mlx_ptr,
		"button/no_down.xpm", &infos->edit_button[1].button_down.w, &infos->edit_button[1].button_down.h);
	infos->button[0].button_up.img_ptr = mlx_xpm_file_to_image(infos->mlx_ptr,
		"button/play_up.xpm", &infos->button[0].button_up.w, &infos->button[0].button_up.h);
	infos->button[0].button_down.img_ptr = mlx_xpm_file_to_image(infos->mlx_ptr,
		"button/play_down.xpm", &infos->button[0].button_down.w, &infos->button[0].button_down.h);
	infos->button[1].button_up.img_ptr = mlx_xpm_file_to_image(infos->mlx_ptr,
		"button/map_up.xpm", &infos->button[1].button_up.w, &infos->button[1].button_up.h);
	infos->button[1].button_down.img_ptr = mlx_xpm_file_to_image(infos->mlx_ptr,
		"button/map_down.xpm", &infos->button[1].button_down.w, &infos->button[1].button_down.h);
	infos->button[2].button_up.img_ptr = mlx_xpm_file_to_image(infos->mlx_ptr,
		"button/edit_up.xpm", &infos->button[2].button_up.w, &infos->button[2].button_up.h);
	infos->button[2].button_down.img_ptr = mlx_xpm_file_to_image(infos->mlx_ptr,
		"button/edit_down.xpm", &infos->button[2].button_down.w, &infos->button[2].button_down.h);
	infos->button[3].button_up.img_ptr = mlx_xpm_file_to_image(infos->mlx_ptr,
		"button/quit_up.xpm", &infos->button[3].button_up.w, &infos->button[3].button_up.h);
	infos->button[3].button_down.img_ptr = mlx_xpm_file_to_image(infos->mlx_ptr,
		"button/quit_down.xpm", &infos->button[3].button_down.w, &infos->button[3].button_down.h);
	infos->edit_button[0].button_up.img = ft_get_img_tex(infos->edit_button[0].button_up.img, infos->edit_button[0].button_up.img_ptr);
	infos->edit_button[0].button_down.img = ft_get_img_tex(infos->edit_button[0].button_down.img, infos->edit_button[0].button_down.img_ptr);
	infos->edit_button[1].button_up.img = ft_get_img_tex(infos->edit_button[1].button_up.img, infos->edit_button[1].button_up.img_ptr);
	infos->edit_button[1].button_down.img = ft_get_img_tex(infos->edit_button[1].button_down.img, infos->edit_button[1].button_down.img_ptr);
	infos->button[0].button_up.img = ft_get_img_tex(infos->button[0].button_up.img, infos->button[0].button_up.img_ptr);
	infos->button[0].button_down.img = ft_get_img_tex(infos->button[0].button_down.img, infos->button[0].button_down.img_ptr);
	infos->button[1].button_up.img = ft_get_img_tex(infos->button[1].button_up.img, infos->button[1].button_up.img_ptr);
	infos->button[1].button_down.img = ft_get_img_tex(infos->button[1].button_down.img, infos->button[1].button_down.img_ptr);
	infos->button[2].button_up.img = ft_get_img_tex(infos->button[2].button_up.img, infos->button[2].button_up.img_ptr);
	infos->button[2].button_down.img = ft_get_img_tex(infos->button[2].button_down.img, infos->button[2].button_down.img_ptr);
	infos->button[3].button_up.img = ft_get_img_tex(infos->button[3].button_up.img, infos->button[3].button_up.img_ptr);
	infos->button[3].button_down.img = ft_get_img_tex(infos->button[3].button_down.img, infos->button[3].button_down.img_ptr);
	infos->button[0].press = 0;
	infos->button[1].press = 0;
	infos->button[2].press = 0;
	infos->button[3].press = 0;
	infos->button[0].x = WIDTH / 2 - infos->button[0].button_up.w / 2;
	infos->button[1].x = WIDTH / 2 - infos->button[1].button_up.w / 2;
	infos->button[2].x = WIDTH / 2 - infos->button[2].button_up.w / 2;
	infos->button[3].x = WIDTH / 2 - infos->button[3].button_up.w / 2;
	infos->button[0].y = HEIGHT * 0.40 - infos->button[0].button_up.h / 2;
	infos->button[1].y = HEIGHT * 0.55 - infos->button[1].button_up.h / 2;
	infos->button[2].y = HEIGHT * 0.70 - infos->button[2].button_up.h / 2;
	infos->button[3].y = HEIGHT * 0.85 - infos->button[3].button_up.h / 2;
	// ft_load_img_bt(infos);
}
// void	ft_load_button(t_window *infos)
// {

// 	if (!(infos->button = malloc(sizeof(t_image) * (1))))
// 		return ;
// 	infos->button[0].img_ptr = mlx_xpm_file_to_image(infos->mlx_ptr, "button/play_up.xpm", &infos->button[0].w, &infos->button[0].h );
// 	infos->button[0].img = ft_get_img_tex(infos->button[0].img, infos->button[0].img_ptr);
// 	// printf("couleur 1 = %x\n", infos->button[0].img[0]);
// 	ft_putendl("egrbe");
// }

static void	ft_load_texture(t_window *infos)
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
	printf("LA SIZE EST : %d\n", size);
	infos->nb_tex_tb = size;
	free(line);
	if (!(infos->texture = malloc(sizeof(t_image) * (size + 1))))
		return ;
	while (get_next_line(fd, &line) > 0)
	{
		path = ft_strjoin("textures/", line);
		infos->texture[i].img_ptr = mlx_xpm_file_to_image(infos->mlx_ptr, path, &infos->texture[i].w, &infos->texture[i].h );
		if (infos->texture[i].img_ptr == NULL)
			printf("omagalul c'est pas de ma faute\n");
		free(line);
		free(path);
		i++;
	}
	i = 0;
	while (i < size)
	{
		ft_putendl("combien de fois je charge les textures");
		infos->texture[i].img = ft_get_img_tex(infos->texture[i].img, infos->texture[i].img_ptr);
		i++;
	}
	close(fd);
}

void	ft_init_wolf(t_window *infos)
{
	double	camx;

	camx = 2 * (WIDTH / 2) / (double)WIDTH - 1;
	// infos->wolf.angle_cam = 0.349066;
	// infos->wolf.angle_cam = 0.0;
	// infos->wolf.d_camscreen = (WIDTH / 2) / tan(FOV / 2);
	// ft_putendl("avant load rd");
	// ft_putendl("apres load rd");
	ft_load_texture(infos);
	ft_load_button(infos);
	if (!(infos->gui = malloc(sizeof(t_image) * (4))))
		return ;
	infos->title.img_ptr = mlx_xpm_file_to_image(infos->mlx_ptr, "Title.xpm", &infos->title.w, &infos->title.h);
	infos->title.img = ft_get_img_tex(infos->title.img, infos->title.img_ptr);
	infos->gui[0].img_ptr = mlx_xpm_file_to_image( infos->mlx_ptr, "gui.xpm", &infos->gui[0].w, &infos->gui[0].h );
	infos->gui[0].img = ft_get_img_tex(infos->gui[0].img, infos->gui[0].img_ptr);
	infos->gui[1].img_ptr = mlx_xpm_file_to_image( infos->mlx_ptr, "gui_select.xpm", &infos->gui[1].w, &infos->gui[1].h );
	infos->gui[1].img = ft_get_img_tex(infos->gui[1].img, infos->gui[1].img_ptr);
	infos->gui[2].img_ptr = mlx_xpm_file_to_image( infos->mlx_ptr, "Briquet.xpm", &infos->gui[2].w, &infos->gui[2].h );
	infos->gui[2].img = ft_get_img_tex(infos->gui[2].img, infos->gui[2].img_ptr);
	infos->wolf.editor = 0;
	infos->wolf.menu = 1;
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
	infos->edit_menu = 0;
	infos->map_menu = 0;
	infos->save_map = 0;
	infos->nb_rd_button = 0;
	ft_load_rd_button(infos);
}