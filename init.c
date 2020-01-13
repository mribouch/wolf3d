/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 17:58:11 by mribouch          #+#    #+#             */
/*   Updated: 2020/01/13 19:54:06 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	ft_load_button(t_window *infos)
{
	if (!(infos->button = malloc(sizeof(t_button) * (5))))
		return ;
	if (!(infos->edit_button = malloc(sizeof(t_button) * 3)))
		return ;
	ft_load_button_up(infos);
	ft_load_button_down(infos);
	ft_load_img_button_up(infos);
	ft_load_img_button_down(infos);
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
}

static void	ft_load_gui_tex(t_window *infos)
{
	int	i;

	i = -1;
	while (++i < infos->nb_tex_tb)
		infos->texture[i].img = ft_get_img_tex(infos->texture[i].img,
			infos->texture[i].img_ptr);
	if (!(infos->gui = malloc(sizeof(t_image) * (3))))
		return ;
	infos->title.img_ptr = mlx_xpm_file_to_image(infos->mlx_ptr,
		"gui/Title.xpm", &infos->title.w, &infos->title.h);
	infos->title.img = ft_get_img_tex(infos->title.img, infos->title.img_ptr);
	infos->gui[0].img_ptr = mlx_xpm_file_to_image(infos->mlx_ptr, "gui/gui.xpm",
		&infos->gui[0].w, &infos->gui[0].h);
	infos->gui[0].img = ft_get_img_tex(infos->gui[0].img,
		infos->gui[0].img_ptr);
	infos->gui[1].img_ptr = mlx_xpm_file_to_image(infos->mlx_ptr,
		"gui/gui_select.xpm", &infos->gui[1].w, &infos->gui[1].h);
	infos->gui[1].img = ft_get_img_tex(infos->gui[1].img,
		infos->gui[1].img_ptr);
}

static void	ft_load_texture(t_window *infos)
{
	int		i;
	int		fd;
	char	*line;
	char	*path;

	fd = open("textures.txt", O_RDONLY);
	i = 0;
	if (get_next_line(fd, &line) <= 0)
		return ;
	infos->nb_tex_tb = ft_atoi(line);
	free(line);
	if (!(infos->texture = malloc(sizeof(t_image) * (infos->nb_tex_tb + 1))))
		return ;
	while (get_next_line(fd, &line) > 0)
	{
		path = ft_strjoin("textures/", line);
		infos->texture[i].img_ptr = mlx_xpm_file_to_image(infos->mlx_ptr,
			path, &infos->texture[i].w, &infos->texture[i].h);
		free(line);
		free(path);
		i++;
	}
	i = -1;
	close(fd);
}

static int	ft_load_var_wolf(t_window *infos, double camx)
{
	infos->wolf.editor = 0;
	infos->wolf.menu = 1;
	infos->wolf.explode = 0;
	infos->wolf.exp_iter = 0;
	infos->wolf.select_block = 0;
	infos->wolf.edit_distance_wall = 3;
	infos->wolf.plane.x = 0;
	infos->wolf.plane.y = 0.66;
	if (ft_spawn_cam(infos) == 0)
		return (0);
	infos->wolf.dir_cam.x = -1;
	infos->wolf.dir_cam.y = 0;
	infos->wolf.dir_cam.color = 0x00FF00;
	infos->map.map_pos.x = 0;
	infos->map.map_pos.y = 0;
	infos->wolf.old_block.x = (int)(infos->wolf.pos_cam.x +
		infos->wolf.dir_cam.x * 3 + infos->wolf.plane.x * camx);
	infos->wolf.old_block.y = (int)(infos->wolf.pos_cam.y +
		infos->wolf.dir_cam.y * 3 + infos->wolf.plane.y * camx);
	infos->wolf.old_block.color = 0;
	infos->edit_menu = 0;
	infos->map_menu = 0;
	infos->save_map = 0;
	infos->nb_rd_button = 0;
	return (1);
}

void		ft_init_wolf(t_window *infos)
{
	double	camx;

	camx = 2 * (WIDTH / 2) / (double)WIDTH - 1;
	ft_load_texture(infos);
	ft_load_button(infos);
	ft_load_gui_tex(infos);
	if (ft_load_var_wolf(infos, camx) == 0)
	{
		ft_putendl("Error: There is no empty space in the map !");
		ft_free_map(infos);
		ft_free_button(infos);
		ft_free_texture(infos);
		mlx_destroy_image(infos->mlx_ptr, infos->game.img_ptr);
		mlx_destroy_window(infos->mlx_ptr, infos->win_ptr);
		exit(0);
	}
	ft_load_rd_button(infos);
}
