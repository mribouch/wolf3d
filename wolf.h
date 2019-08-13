/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:13:15 by mribouch          #+#    #+#             */
/*   Updated: 2019/08/13 14:22:23 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H
# include "libft/libft.h"
# include "minilibx_macos/mlx.h"
#include "callbacks.h"
#include "key.h"
# define WIDTH 1000
# define HEIGHT 1000

typedef struct	s_square
{
	int			x;
	int			y;
	int			size;
	int			color;
}				t_square;

typedef struct	s_circle
{
	int			x;
	int			y;
	int			d;
	int			r;
}				t_circle;

typedef struct	s_coord3d
{
	double		x;
	double		y;
	double		z;
}				t_coord3d;

typedef struct	s_bresen
{
	float		dx;
	float		dy;
	int			i;
	int			xinc;
	int			yinc;
	float		cumul;
	float		x;
	float		y;
}				t_bresen;

typedef struct	s_var
{
	int			color1;
	int			color2;
}				t_var;

typedef struct	s_color
{
	int	r;
	int	g;
	int	b;
}				t_color;

typedef struct	s_coord2d
{
	double			x;
	double			y;
	int				color;
}				t_coord2d;

typedef struct	s_wolf
{
	t_coord2d	pos_cam;
	double		angle_cam;
	t_coord2d	dir_cam;
	int			fov;
	int			d_camscreen;

}				t_wolf;


typedef struct	s_map
{
	int				**map;
	t_coord2d		map_pos;
	int				width;
	int				height;
}				t_map;

typedef struct	s_window
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	int			*img;
	int			width;
	int			height;
	t_map		map;
	t_key		keys;
	t_coord2d	test;
	t_coord2d	cursor;
	t_wolf		wolf;
	t_wolf		*data;
}				t_window;

void			ft_fill_key(t_window *infos);
int				ft_dealkey_press(int keycode, t_window *infos);
int				ft_dealk_release(int keycode, t_window *infos);
int				ft_callback(t_window *infos);
int				**ft_get_map(int fd, t_window *infos);
void			ft_line_new(t_window *infos, t_coord2d v1, t_coord2d v2);
void			ft_init_wolf(t_window *infos);
void			ft_fullcircle(t_window *infos, t_coord2d c, int r, int color);
void			ft_circle(t_window *infos, t_coord2d c, int r, int color);
void			ft_fill_square(t_window *infos, t_square s);
void			ft_square(t_window *infos, t_square s);
void			ft_draw_cam(t_window *infos);
void			ft_draw_minimap(t_window *infos, t_coord2d coordmap);

#endif