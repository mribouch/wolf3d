/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 17:22:54 by mribouch          #+#    #+#             */
/*   Updated: 2019/11/22 16:17:55 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

#   include <stdio.h>
# include <dirent.h>

void	ft_print_rd_bt(t_window *infos)
{
	int	i;
	t_coord2d coord;

	i = 0;
	while (i < infos->nb_rd_button)
	{
		coord.x = infos->rd_button[i].x;
		coord.y = infos->rd_button[i].y;
		// printf("x = %f, y = %f\n", coord.x, coord.y);
		ft_fullcircle(infos, coord, 8, 0xFFFFFF);
		if (infos->rd_button[i].checked == 1)
			ft_fullcircle(infos, coord, 5, 0x000000);
		i++;
	}
}

void	ft_save(t_window *infos)
{
	int	fd;
	int	i;
	int	j;
	char	*line;

	if (!(line = malloc(sizeof(char) * (infos->map.width * 2 - 2))))
		return ;
	i = 0;
	j = 0;
	fd = open(infos->map.name, O_WRONLY);
	while (i < infos->map.height)
	{
		while (j < infos->map.width)
		{
			line[j] = *ft_itoa(infos->map.map[i][j]);
			ft_putchar_fd(line[j], fd);
			if (j < infos->map.width - 1)
				ft_putchar_fd(' ', fd);
			j++;
		}
		if (i < infos->map.height - 1)
		ft_putchar_fd('\n', fd);
		j = 0;
		i++;
	}
	close(fd);
}

void	ft_edit(t_window *infos)
{
	infos->edit_button[0].x = WIDTH/2 - infos->edit_button[0].button_up.w;
	infos->edit_button[1].x = WIDTH/2 + 50;
	infos->edit_button[0].y = HEIGHT/2;
	infos->edit_button[1].y = HEIGHT/2;
	infos->edit_button[0].press = 0;
	infos->edit_button[1].press = 0;
	infos->edit_menu = 1;
	infos->wolf.menu = 0;
}