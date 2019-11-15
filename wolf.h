/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:13:15 by mribouch          #+#    #+#             */
/*   Updated: 2019/11/15 05:19:03 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "minilibx_macos/mlx.h"
# include "callbacks.h"
# include "key.h"
# include <time.h>
# define WIDTH 916
# define HEIGHT 688
# define RAYLENGHT 150.0
# define FOV 1.5708
# define NUM_TEX 8

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

typedef struct  s_hsv
{
        double                  h;
        double                  s;
        double                  v;
}                               t_hsv;

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

typedef	struct s_dda
{
	t_coord2d	cam;
	t_coord2d	raydir;
	t_coord2d	side_dist;
	t_coord2d	delta_dist;
	t_coord2d	step;
	t_coord2d	map;
	int			side;
	int			hit;
	double		wall_x;
	int			tex_x;
	int			tex_y;
	int			d;
	int			line_height;
	double		perp_wall_dist;
	int			draw_start;
	int			draw_end;
}				t_dda;

typedef struct	s_ray
{
	t_coord2d	pos_ray;
	t_coord2d	pos_int;
	float		length;
	float		angle;
}				t_ray;

typedef struct	s_wolf
{
	t_coord2d	pos_cam;
	t_coord2d	dir_cam;
	t_coord2d	plane;
	t_coord2d	old_block;
	t_coord2d	current_block;
	t_ray		*tab_ray;
	t_coord2d	tnt_block;
	int			block_dist;
	int			menu;
	double		angle_cam;
	int			fov;
	int			explode;
	int			exp_iter;
	int			d_camscreen;
	int			s_wall;
	int			editor;
	int			select_block;
	int			edit_distance_wall;
}				t_wolf;


typedef struct	s_map
{
	int				**map;
	t_coord2d		map_pos;
	int				width;
	int				height;
	char			*name;
}				t_map;

typedef struct	s_image
{
	int			*img;
	void		*img_ptr;
	int			w;
	int			h;
}				t_image;

typedef struct	s_r_button
{
	int			x;
	int			y;
	int			checked;
	char		*data;
}				t_rd_button;

typedef struct	s_button
{
	t_image		button_up;
	t_image		button_down;
	int			press;
	int			x;
	int			y;
}				t_button;

typedef struct	s_window
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_image		game;
	t_image		menu;
	int			map_menu;
	int			edit_menu;
	int			save_map;
	clock_t		previous;
	double		lag;
	t_map		map;
	t_key		keys;
	t_coord2d	test;
	t_coord2d	cursor;
	t_wolf		wolf;
	t_wolf		*data;
	t_image		*texture;
	t_button	*button;
	t_button	*edit_button;
	t_rd_button	*rd_button;
	int			nb_rd_button;
	int			nb_tex_tb;
	t_image		*gui;
}				t_window;

void			ft_fill_key(t_window *infos);
int				ft_dealkey_press(int keycode, t_window *infos);
int				ft_dealk_release(int keycode, t_window *infos);
void			ft_putmenu(t_window *infos);
int				ft_get_cursor(int x, int y, t_window *infos);
int				ft_callback(t_window *infos);
int				**ft_get_map(int fd, t_window *infos);
void			ft_line_new(t_window *infos, t_coord2d v1, t_coord2d v2);
void			ft_init_wolf(t_window *infos);
void			ft_init_ray(t_window *infos);
void			ft_update_ray(t_window *infos);
void			ft_draw_cam(t_window *infos);
void			ft_draw_minimap(t_window *infos, t_coord2d coordmap);
void			ft_draw_ray(t_window *infos);
void			ft_draw_wolf(t_window *infos, t_dda dda, double perp_wall_dist, int x);
void			ft_draw_cursor(t_window *infos);
void			ft_dealk_act(t_window *infos);
int				ft_button_press(int button, int x, int y, t_window *infos);
int				ft_button_release(int button, int x, int y, t_window *infos);
void			ft_draw_select_block(t_window *infos);
void			ft_draw_item_tb(t_window *infos);
int				ft_create_rgb(double r, double g, double b);
t_hsv			ft_rgb2hsv(t_color color);
int				ft_negative_col(t_color color);
t_color			ft_int_to_rgb(int color);
int     		ft_get_tnt_color(t_window *infos, int color1, int color2, int nbp);
int				ft_lerp(int i, int color1, int color2, float nbp);
int				ft_get_lerp_tnt(t_window *infos, int color1, int color2, int nbp);
int				ft_get_lerp_dist(t_window *infos, int color1, int nbp);
int				ft_get_color_dist(t_window *infos, t_hsv color);
int				ft_manage_button(t_window *infos, int x, int y, int id);
int				ft_manage_yn_button(t_window *infos, int x, int y, int id);
void			ft_button_yn_in_game(t_window *infos, int id, t_image up_down);
void			ft_manage_rd_bt(t_window *infos);
void			ft_edit(t_window *infos);
void			ft_print_rd_bt(t_window *infos);
void			ft_print_yn_button(t_window *infos);
void			ft_save_world(t_window *infos);
void			ft_print_map(t_window *infos);
void			ft_square(t_window *infos, t_image img, t_square s);
void			ft_fill_square(t_window *infos, t_image img, t_square s);
void			ft_circle(t_window *infos, t_coord2d c, int r, int color);
void			ft_fullcircle(t_window *infos, t_coord2d c, int r, int color);
void			ft_load_rd_button(t_window *infos);
void    		ft_check_map(t_window *infos);

#endif