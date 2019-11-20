/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 16:58:17 by mribouch          #+#    #+#             */
/*   Updated: 2019/11/20 17:33:23 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

#include <stdio.h>
#include <math.h>

static void	ft_draw_item_tb(t_window *infos)
{
	int	i;

	i = 0;
	while (i < infos->nb_tex_tb)
	{
		mlx_put_image_to_window(infos->mlx_ptr,
    		infos->win_ptr, infos->texture[i].img_ptr, WIDTH / 2 -
				infos->gui[0].w / 2 + 2 + (infos->texture[i].w + 4) * i, HEIGHT - infos->texture[i].h -
					(infos->gui[0].h - infos->texture[i].h) / 2);
		i++;
	}
}

static void	ft_draw_select_block(t_window *infos)
{
	int	x;
	int	y;

	y = HEIGHT - infos->gui[1].h;
	x = WIDTH / 2 - infos->gui[0].w / 2 - 1 + (infos->gui[1].w - 2) * infos->wolf.select_block;
	mlx_put_image_to_window(infos->mlx_ptr,
    	infos->win_ptr, infos->gui[1].img_ptr, x, y);
}

static void	ft_get_col_tex(t_window *infos, t_dda dda, int x, int tex_num)
{
	int	color;
	int	i;
	int	y;

	i = 0;
	if (dda.side == 0)
		dda.wall_x = infos->wolf.pos_cam.y + dda.perp_wall_dist * dda.raydir.y;
	else
		dda.wall_x = infos->wolf.pos_cam.x + dda.perp_wall_dist * dda.raydir.x;
	dda.wall_x -= floorf(dda.wall_x);
	dda.tex_x = (int)(dda.wall_x * infos->texture[tex_num].w);
	if (dda.side == 0 && dda.raydir.x > 0)
		dda.tex_x = infos->texture[tex_num].w - dda.tex_x - 1;
	if (dda.side == 1 && dda.raydir.y < 0)
		dda.tex_x = infos->texture[tex_num].w - dda.tex_x - 1;
	i = dda.draw_start;
	while(i < dda.draw_end)
	{
		dda.d = i * 256 - HEIGHT * 128 + dda.line_height * 128;
		dda.tex_y = ((dda.d * infos->texture[tex_num].h) / dda.line_height) / 256;
		color = infos->texture[tex_num].img[infos->texture[tex_num].h * dda.tex_y + dda.tex_x];
		if (dda.side == 1)
			color = (color >> 1) & 8355711;
		if ((int)infos->wolf.tnt_block.x == (int)dda.map.x && (int)infos->wolf.tnt_block.y == (int)dda.map.y && infos->wolf.explode == 1)
			color = ft_get_lerp_tnt(infos, color, 0xFFFFFF, 100 / 4);
		// ft_putendl("heyyyy");
		infos->wolf.block_dist = dda.perp_wall_dist;
		// color = ft_get_lerp_dist(infos, color, 10);
		infos->game.img[x + i++ * WIDTH] = color;
	}
    if(dda.side == 0 && dda.raydir.x > 0)
    {
      dda.floor_wall.x = dda.map.x;
      dda.floor_wall.y = dda.map.y + dda.wall_x;
    }
    else if(dda.side == 0 && dda.raydir.x < 0)
    {
      dda.floor_wall.x = dda.map.x + 1.0;
      dda.floor_wall.y = dda.map.y + dda.wall_x;
    }
    else if(dda.side == 1 && dda.raydir.y > 0)
    {
      dda.floor_wall.x = dda.map.x + dda.wall_x;
      dda.floor_wall.y = dda.map.y;
    }
    else
    {
      dda.floor_wall.x = dda.map.x + dda.wall_x;
      dda.floor_wall.y = dda.map.y + 1.0;
    }
    dda.distwall = dda.perp_wall_dist;
    dda.distplayer = 0.0;
    if (dda.draw_end < 0) dda.draw_end = HEIGHT;
	y = dda.draw_end;
	while (y < HEIGHT)
    {
    	dda.cur_dist = HEIGHT / (2.0 * y - HEIGHT);
        dda.weight = (dda.cur_dist - dda.distplayer) / (dda.distwall - dda.distplayer);
        dda.cur_floor.x = dda.weight * dda.floor_wall.x + (1.0 - dda.weight) * infos->wolf.pos_cam.x;
        dda.cur_floor.y = dda.weight * dda.floor_wall.y + (1.0 - dda.weight) * infos->wolf.pos_cam.y;
        dda.floor_tex.x = (int)(dda.cur_floor.x * infos->texture[2].w * 2) % infos->texture[2].w;
        dda.floor_tex.y = (int)(dda.cur_floor.y * infos->texture[2].h * 2) % infos->texture[2].h;
		color = (infos->texture[2].img[infos->texture[2].w * (int)dda.floor_tex.y + (int)dda.floor_tex.x]);
        // color = ft_get_lerp_dist(infos, color, 10);
		infos->game.img[x + y * WIDTH] = color;
		color = infos->texture[2].img[infos->texture[2].w * (int)dda.floor_tex.y + (int)dda.floor_tex.x];
        infos->game.img[x + (HEIGHT - y) * WIDTH] = color;
      	y++;
	}
}

void	ft_draw_wolf(t_window *infos, t_dda dda, double perp_wall_dist, int x)
{
	int	color;
	int	tex_num;

	tex_num = infos->map.map[(int)dda.map.y][(int)dda.map.x];
	if (tex_num > 0)
		tex_num = infos->map.map[(int)dda.map.y][(int)dda.map.x] - 1;
	// (void)texNum;
	dda.perp_wall_dist = perp_wall_dist;
	color = 0xFFFFFF;
	dda.line_height = (int)(HEIGHT / dda.perp_wall_dist);
	dda.draw_start = -dda.line_height / 2 + HEIGHT / 2;
	if (dda.draw_start < 0)
		dda.draw_start = 0;
	dda.draw_end = dda.line_height / 2 + HEIGHT / 2;
	if (dda.draw_end >= HEIGHT)
		dda.draw_end = HEIGHT - 1;
	if (dda.side == 1)
		color = 0xDDDDDD;
	// infos->wolf.block_dist = sqrtf(powf(dda.map.x - infos->wolf.pos_cam.x, 2) + powf(dda.map.y - infos->wolf.pos_cam.y, 2));
	// infos->wolf.block_dist = sqrtf((dda.map.x * dda.map.x - 2 * dda.map.x * infos->wolf.pos_cam.x +
	// 	infos->wolf.pos_cam.x * infos->wolf.pos_cam.x) + (dda.map.y * dda.map.y - 2 *
	// 		dda.map.y * infos->wolf.pos_cam.y + infos->wolf.pos_cam.y * infos->wolf.pos_cam.y));
	ft_get_col_tex(infos, dda, x, tex_num);
}

void	ft_draw_cursor(t_window *infos)
{
	int	size;
	int	i;
	t_color	current_rgb;
	int		current_int;
	int		neg_col;

	size = 15;
	i = 0;
	while (i < size)
	{
		current_int = infos->game.img[WIDTH / 2 - size / 2 + i + HEIGHT / 2 * WIDTH];
		current_rgb = ft_int_to_rgb(current_int);
		neg_col = ft_negative_col(current_rgb);
		infos->game.img[WIDTH / 2 - size / 2 + i + HEIGHT / 2 * WIDTH] = neg_col;
		i++;
	}
	i = 0;
	while(i < size)
	{
		if (i != 7)
		{
			current_int = infos->game.img[WIDTH / 2 + (HEIGHT / 2 - size / 2 + i) * WIDTH];
			current_rgb = ft_int_to_rgb(current_int);
			neg_col = ft_negative_col(current_rgb);
			// printf("col neg = %x\n", neg_col);
			infos->game.img[WIDTH / 2 + (HEIGHT / 2 - size / 2 + i) * WIDTH] = neg_col;
		}
		i++;
	}
}

void	ft_draw(t_window *infos)
{
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
		if (infos->wolf.select_block == 7)
			mlx_put_image_to_window(infos->mlx_ptr,
    			infos->win_ptr, infos->gui[2].img_ptr, WIDTH - infos->gui[2].w,
					HEIGHT - infos->gui[2].h);
	}
}