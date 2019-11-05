/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 16:58:17 by mribouch          #+#    #+#             */
/*   Updated: 2019/11/04 15:12:22 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

#include <stdio.h>
#include <math.h>


// void	ft_draw_col(t_window *infos, float up, float dwn, int it)
// {
// 	int	i;

// 	i = 0;
// 	while (i < HEIGHT)
// 	{
// 		if (infos->wolf.tab_ray[it].length == RAYLENGHT)
// 		{
// 			if (i <= HEIGHT / 2)
// 				infos->img[WIDTH - it + i++ * WIDTH] = 0x392C02;
// 			else
// 				infos->img[WIDTH - it + i++ * WIDTH] = 0x765E10;
// 		}
// 		else if (i < (int)up)
// 		{
// 			infos->img[WIDTH - it + i++ * WIDTH] = 0x392C02;
// 		}
// 		else if (i >= (int)up && i <= (int)dwn)
// 			infos->img[WIDTH - it + i++ * WIDTH] = 0xB8B8B8;
// 		else if (i > (int)dwn)
// 			infos->img[WIDTH - it + i++ * WIDTH] = 0x765E10;
// 			// printf("voici i = %d\n", i);
// 	}
// }

void	ft_draw_item_tb(t_window *infos)
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

void	ft_draw_select_block(t_window *infos)
{
	int	x;
	int	y;

	y = HEIGHT - infos->gui[1].h;
	x = WIDTH / 2 - infos->gui[0].w / 2 - 1 + (infos->gui[1].w - 2) * infos->wolf.select_block;
	mlx_put_image_to_window(infos->mlx_ptr,
    	infos->win_ptr, infos->gui[1].img_ptr, x, y);
}

void	ft_get_col_tex(t_window *infos, t_dda dda, int x, int tex_num)
{
	int	color;
	int	i;

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
			color = ft_get_tnt_color(infos, color, 0xFFFFFF, 100);
		// ft_putendl("heyyyy");
		infos->wolf.block_dist = dda.perp_wall_dist;
		// color = ft_get_lerp_dist(infos, color, 10);
		// color = ft_get_color_dist(infos, ft_rgb2hsv(ft_int_to_rgb(color)));
		infos->game.img[x + i++ * WIDTH] = color;
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

// void	ft_draw_ray(t_window *infos)
// {
// 	int	i;
// 	t_coord2d	pos_cam_mm;

// 	pos_cam_mm.x = 100;
// 	pos_cam_mm.y = 100;
// 	pos_cam_mm.color = 0x00FF00;
// 	i = 0;
// 	while (i < WIDTH)
// 	{
// 		// infos->wolf.tab_ray[i].length /= cos(infos->wolf.tab_ray[i].angle);
// 		infos->wolf.tab_ray[i].pos_ray.x -= (infos->wolf.pos_cam.x - pos_cam_mm.x);
// 		infos->wolf.tab_ray[i].pos_ray.y -= (infos->wolf.pos_cam.y - pos_cam_mm.y);
// 		ft_line_new(infos, pos_cam_mm, infos->wolf.tab_ray[i].pos_ray);
// 		i++;
// 	}
// }

// void	ft_draw_cam(t_window *infos)
// {
// 	t_coord2d	coordcam;

// 	// coordcam.x = infos->wolf.pos_cam.x;
// 	// coordcam.y = infos->wolf.pos_cam.y;
// 	coordcam.x = 100;
// 	coordcam.y = 100;
// 	coordcam.color = 0xDD1212;
// 	ft_fullcircle(infos, coordcam, 3, 0xDD1212);
// }

// void	ft_draw_fence(t_window *infos)
// {
// 	t_square	fence;

// 	fence.size = 200;
// 	fence.x = 0;
// 	fence.y = 0;
// 	fence.color = 0xFF0000;
// 	ft_square(infos, fence);
// }

// void	ft_draw_minimap(t_window *infos, t_coord2d coordmap)
// {
// 	t_square	sq;
// 	int			i;
// 	int			j;

// 	i = 0;
// 	j = 0;
// 	ft_draw_fence(infos);
// 	sq.size = 24;
// 	sq.x = coordmap.x;
// 	sq.y = coordmap.y;
// 	while (i < infos->map.height)
// 	{
// 		while (j < infos->map.width)
// 		{
// 			if (infos->map.map[i][j] == 0)
// 				sq.color = 0xFFFFFF;
// 			else
// 				sq.color = 0x0000FF;
// 			if ((sq.x < 200 - sq.size && sq.x >= 0) && (sq.y < 200 - sq.size && sq.y >= 0))
// 				ft_fill_square(infos, sq);
// 			sq.x += sq.size;
// 			j++;
// 		}
// 		j = 0;
// 		i++;
// 		sq.x = coordmap.x;
// 		sq.y += sq.size;
// 	}
// }

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