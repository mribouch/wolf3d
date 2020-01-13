/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 17:22:54 by mribouch          #+#    #+#             */
/*   Updated: 2020/01/13 15:20:11 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static t_coord2d	ft_init_cb(t_window *infos)
{
	t_coord2d	cb;
	double		camx;

	camx = 2 * (WIDTH / 2) / (double)WIDTH - 1;
	cb.x = infos->wolf.pos_cam.x + infos->wolf.dir_cam.x *
		infos->wolf.edit_distance_wall + infos->wolf.plane.x * camx;
	cb.y = infos->wolf.pos_cam.y + infos->wolf.dir_cam.y *
		infos->wolf.edit_distance_wall + infos->wolf.plane.y * camx;
	return (cb);
}

void				ft_editor(t_window *infos)
{
	t_coord2d	cb;

	cb = ft_init_cb(infos);
	if ((cb.x <= 0 || cb.x >= infos->map.width) ||
		(cb.y <= 0 || cb.y >= infos->map.height))
		return ;
	if (cb.x != infos->wolf.old_block.x && cb.y != infos->wolf.old_block.y)
	{
		if (infos->map.map[(int)cb.y][(int)cb.x] == 0)
		{
			if (infos->wolf.old_block.color == 0)
				infos->map.map[(int)infos->wolf.old_block.y]
					[(int)infos->wolf.old_block.x] = 0;
			if (infos->wolf.select_block < 7)
				infos->map.map[(int)cb.y][(int)cb.x] =
					infos->wolf.select_block + 1;
			infos->wolf.old_block.x = cb.x;
			infos->wolf.old_block.y = cb.y;
			infos->wolf.old_block.color = 0;
		}
	}
}

void				ft_print_rd_bt(t_window *infos)
{
	int			i;
	t_coord2d	coord;

	i = 0;
	while (i < infos->nb_rd_button)
	{
		coord.x = infos->rd_button[i].x;
		coord.y = infos->rd_button[i].y;
		ft_fullcircle(infos, coord, 8, 0xFFFFFF);
		if (infos->rd_button[i].checked == 1)
			ft_fullcircle(infos, coord, 5, 0x000000);
		i++;
	}
}

static char			*ft_write_file(t_window *infos, int fd, char *line, int i)
{
	char	*tmp;
	int		j;

	j = 0;
	while (j < infos->map.width)
	{
		tmp = ft_itoa(infos->map.map[i][j]);
		line[j] = tmp[0];
		ft_putchar_fd(line[j], fd);
		if (j < infos->map.width - 1)
			ft_putchar_fd(' ', fd);
		j++;
		free(tmp);
	}
	return (line);
}

void				ft_save(t_window *infos)
{
	int		fd;
	int		i;
	char	*line;

	if (!(line = malloc(sizeof(char) * (infos->map.width * 2 - 2))))
		return ;
	i = 0;
	fd = open(infos->map.name, O_WRONLY);
	while (i < infos->map.height)
	{
		line = ft_write_file(infos, fd, line, i);
		if (i < infos->map.height - 1)
			ft_putchar_fd('\n', fd);
		i++;
	}
	free(line);
	close(fd);
}
