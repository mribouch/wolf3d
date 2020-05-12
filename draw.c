/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 16:58:17 by mribouch          #+#    #+#             */
/*   Updated: 2020/01/22 14:48:51 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	ft_draw_item_tb(t_window *infos)
{
	int	i;

	i = 0;
	while (i < infos->nb_tex_tb)
	{
		mlx_put_image_to_window(infos->mlx_ptr,
			infos->win_ptr, infos->texture[i].img_ptr, WIDTH / 2 -
				infos->gui[0].w / 2 + 2 + (infos->texture[i].w + 4) *
					i, HEIGHT - infos->texture[i].h -
						(infos->gui[0].h - infos->texture[i].h) / 2);
		i++;
	}
}

static void	ft_draw_select_block(t_window *infos)
{
	int	x;
	int	y;

	y = HEIGHT - infos->gui[1].h;
	x = WIDTH / 2 - infos->gui[0].w / 2 - 1 + (infos->gui[1].w - 2) *
		infos->wolf.select_block;
	mlx_put_image_to_window(infos->mlx_ptr,
		infos->win_ptr, infos->gui[1].img_ptr, x, y);
}

void		ft_draw_wolf(t_window *infos, t_dda dda, double pwd, int x)
{
	//int	color;
	int	tex_num;

	tex_num = infos->map.map[(int)dda.map.y][(int)dda.map.x];
	if (tex_num > 0)
		tex_num = infos->map.map[(int)dda.map.y][(int)dda.map.x] - 1;
	dda.perp_wall_dist = pwd;
	//color = 0xFFFFFF;
	dda.line_height = (int)(HEIGHT / dda.perp_wall_dist);
	dda.draw_start = -dda.line_height / 2 + HEIGHT / 2;
	if (dda.draw_start < 0)
		dda.draw_start = 0;
	dda.draw_end = dda.line_height / 2 + HEIGHT / 2;
	if (dda.draw_end >= HEIGHT)
		dda.draw_end = HEIGHT - 1;
	//if (dda.side == 1)
	//	color = 0xDDDDDD;
	ft_get_col_tex(infos, dda, x, tex_num);
}

void		ft_draw_cursor(t_window *infos)
{
	int	size;
	int	i;
	int	current_int;

	size = 15;
	i = 0;
	while (i < size)
	{
		current_int = infos->game.img[WIDTH / 2 - size
			/ 2 + i + HEIGHT / 2 * WIDTH];
		infos->game.img[WIDTH / 2 - size / 2 + i++ + HEIGHT / 2 * WIDTH] =
			ft_negative_col(ft_int_to_rgb(current_int));
	}
	i = -1;
	while (i < size - 1)
	{
		if (++i != 7)
		{
			current_int = infos->game.img[WIDTH / 2 +
				(HEIGHT / 2 - size / 2 + i) * WIDTH];
			infos->game.img[WIDTH / 2 + (HEIGHT / 2 - size / 2 + i) * WIDTH] =
				ft_negative_col(ft_int_to_rgb(current_int));
		}
	}
}

void		ft_draw(t_window *infos)
{
	t_coord2d	coord;

	coord.x = WIDTH - (infos->texture[7].w * 13);
	coord.y = HEIGHT - (infos->texture[7].h * 13);
	if (infos->wolf.select_block == 7)
		ft_img_in_game(infos->game, infos->texture[7], coord, 13);
	coord.x = WIDTH - (infos->texture[7].w * 27);
	coord.y = HEIGHT - (infos->texture[7].h * 30);
	if (infos->wolf.select_block == 8)
		ft_img_in_game(infos->game, infos->texture[8], coord, 30);
	mlx_put_image_to_window(infos->mlx_ptr,
		infos->win_ptr, infos->game.img_ptr, 0, 0);
	if (infos->save_map == 1)
		mlx_string_put(infos->mlx_ptr, infos->win_ptr, WIDTH / 2 - WIDTH / 8,
			HEIGHT / 2 - 100, 0xFFFFFF, "Do you want to save the map ?");
	if (infos->map_menu == 1)
		ft_print_map(infos);
	if (infos->wolf.menu == 0)
	{
		mlx_put_image_to_window(infos->mlx_ptr,
			infos->win_ptr, infos->gui[0].img_ptr, WIDTH / 2 -
				infos->gui[0].w / 2, HEIGHT - infos->gui[0].h);
		ft_draw_item_tb(infos);
		ft_draw_select_block(infos);
	}
}
