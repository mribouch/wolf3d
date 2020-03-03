/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_button.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 16:08:48 by mribouch          #+#    #+#             */
/*   Updated: 2020/03/03 14:33:12 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int			ft_manage_yn_button(t_window *infos, int x, int y, int id)
{
	int	w;
	int	h;

	w = infos->edit_button[0].button_up.w;
	h = infos->edit_button[0].button_up.h;
	if (infos->save_map == 1)
	{
		if ((infos->cursor.x >= x && infos->cursor.x <= x + w) &&
			(infos->cursor.y >= y && infos->cursor.y <= y + h) &&
				infos->keys.left_click == 1)
		{
			infos->edit_button[id].press = 1;
			return (1);
		}
		else if ((infos->cursor.x >= x && infos->cursor.x <= x + w) &&
			(infos->cursor.y >= y && infos->cursor.y <= y + h) &&
				infos->keys.left_click == 0 &&
					infos->edit_button[id].press == 1)
			return (2);
		else if (((infos->cursor.x < x || infos->cursor.x > x + w) ||
			(infos->cursor.y < y || infos->cursor.y > y + h)) ||
				infos->keys.left_click == 0)
			infos->edit_button[id].press = 0;
	}
	return (0);
}

void		ft_manage_rd_bt(t_window *infos)
{
	int	i;
	int	last_checked;
	int	tmp;

	i = 0;
	tmp = 0;
	while (i < infos->nb_rd_button)
	{
		if (infos->cursor.x >= infos->rd_button[i].x - 7 &&
			infos->cursor.x <= infos->rd_button[i].x + 10 &&
				infos->cursor.y >= infos->rd_button[i].y - 7 &&
					infos->cursor.y <= infos->rd_button[i].y + 10
						&& infos->keys.left_click == 1)
		{
			infos->rd_button[i].checked = 1;
			last_checked = i;
			while (tmp < infos->nb_rd_button)
			{
				if (tmp != last_checked)
					infos->rd_button[tmp].checked = 0;
				tmp++;
			}
		}
		i++;
	}
}

void		ft_print_map(t_window *infos)
{
	int	i;
	int	y;

	y = 10;
	i = 0;
	while (i < infos->nb_rd_button)
	{
		mlx_string_put(infos->mlx_ptr, infos->win_ptr, 30,
			y, 0xFFFFFF, infos->rd_button[i].data);
		y += 30;
		i++;
	}
}

static void	ft_get_map_name(t_window *infos, int fd, char **line, t_coord2d cor)
{
	char	*name;
	int		i;

	i = 0;
	while (get_next_line(fd, line) > 0)
	{
		infos->rd_button[i].x = cor.x;
		infos->rd_button[i].y = cor.y;
		infos->rd_button[i].checked = 0;
		if (!(infos->rd_button[i].data = malloc(sizeof(char) *
			ft_strlen(*line))))
			return ;
		infos->rd_button[i].data = ft_strcpy(infos->rd_button[i].data, *line);
		name = ft_strjoin("maps/", *line);
		if (ft_strcmp(name, infos->map.name) == 0)
			infos->rd_button[i].checked = 1;
		free(name);
		free(*line);
		cor.y += 30;
		i++;
	}
}

void		ft_load_rd_button(t_window *infos)
{
	int			fd;
	char		*line;
	t_coord2d	coord;

	coord.x = 20;
	coord.y = 20;
	fd = open("maps/maps.txt", O_RDONLY);
	if (get_next_line(fd, &line) <= 0)
		return ;
	infos->nb_rd_button = ft_atoi(line);
	if (!(infos->rd_button = malloc(sizeof(t_rd_button) * (ft_atoi(line) + 1))))
		return ;
	free(line);
	ft_get_map_name(infos, fd, &line, coord);
	close(fd);
}
