/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 15:34:57 by mribouch          #+#    #+#             */
/*   Updated: 2019/04/19 18:12:45 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <fcntl.h>
# include "libft/libft.h"
# include "minilibx_macos/mlx.h"

typedef struct	s_point
{
	float	x;
	float	y;
	float	z;
	int		color;
}				t_point;

typedef struct	s_newv
{
	int	i;
	int	j;
	int	dx;
	int	dy;
	int	v;
}				t_newv;

typedef struct	s_bresen
{
	float	dx;
	float	dy;
	int		i;
	int		xinc;
	int		yinc;
	float	cumul;
	float	x;
	float	y;
}				t_bresen;

typedef struct	s_var
{
	int	color1;
	int	color2;
}				t_var;

typedef struct	s_map
{
	int	**map;
	int	width;
	int	height;
}				t_map;

typedef struct	s_color
{
	int	r;
	int	g;
	int	b;
}				t_color;

typedef struct	s_mod
{
	float	x;
	float	y;
	float	z;
}				t_mod;

typedef struct	s_state
{
	t_mod	size;
	t_mod	rota;
	t_mod	pos;
}				t_state;

typedef struct	s_window
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	int		width;
	int		height;
	int		*img;
	int		colid;
	int		bcol;
	int		boolp;
	t_point	*vertices;
	t_point	*iso;
	t_map	*mapinf;
	t_state	*state;
}				t_window;

typedef union	u_mat4
{
	struct		s_mat4_data
	{
		float	m00;
		float	m01;
		float	m02;
		float	m03;
		float	m10;
		float	m11;
		float	m12;
		float	m13;
		float	m20;
		float	m21;
		float	m22;
		float	m23;
		float	m30;
		float	m31;
		float	m32;
		float	m33;
	}			d;
	float		m[4][4];
}				t_mat4;

int				ft_dealkey(int key, t_window *infos);
t_map			*ft_read(int fd, t_map *mapinf, char ***col);
int				ft_rd_nbc(char *full);
int				ft_rd_nbl(char *full);
int				ft_check_char(char *line);
int				ft_parse_line(char *full, char *line, int lenc);
int				ft_parse_error(char *line);
int				ft_check_error(char *full, char *line);
int				ft_check_return(char *line, char *full);
void			ft_set_color(int key, t_window *infos);
void			ft_draw(t_window *infos);
t_state			*ft_fill_state(t_state *state);
t_state			*ft_fill_persp_state(t_state *state);
int				ft_lerp(int i, int color1, int color2, float nbp);
void			ft_line_new(t_window *infos, t_point vertices1,
					t_point vertices2);
int				*ft_get_img(int *img, void *img_ptr, t_window *infos);
char			**ft_get_col(char **allpoint, char **col);
int				ft_get_num(char *full, int k);
int				ft_get_c(char *full);
int				*ft_get_img_point(t_window *infos);
int				ft_hex2int(char *hex);
char			**ft_strsplit_fdf(char *str);
t_point			*ft_new(t_window *infos, t_point *vertices, char **col);
t_window		*ft_dezoom(t_window *infos);
t_point			*ft_get_caval(t_point *vertices, t_map *mapinf,
					t_var *var, t_window *infos);
t_point			*ft_multmat(t_window *infos, t_mat4 rot);
void			ft_draw_iso(t_window *infos);
void			ft_draw_persp(t_window *infos);
t_point			*ft_iso(t_window *infos);
void			ft_callback(t_window *infos);
void			ft_bcolor(void *s, int color, size_t n);
void			ft_putmenu(t_window *i);
t_mat4			ft_multmat2(t_mat4 rot1, t_mat4 rot2);
t_point			*ft_rot(t_window *infos);
char			*ft_free_join(char *s1, const char *s2);
void			ft_free_dchar(char **tab);
void			ft_free_infos(t_window *infos);
void			ft_free_fullline(char *full, char *line);
void			ft_free_nvfile(t_window *infos, t_map *tmp);
char			*ft_fill_full(char *full, char *line, int *lenc);

#endif
