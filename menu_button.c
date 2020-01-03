/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_button.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 16:08:48 by mribouch          #+#    #+#             */
/*   Updated: 2019/12/04 17:27:43 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "wolf.h"

#       include <stdio.h>
int		ft_manage_yn_button(t_window *infos, int x, int y, int id)
{
	int	w;
	int	h;

	ft_putendl("je suis dedannnns");
	w = infos->edit_button[0].button_up.w;
	h = infos->edit_button[0].button_up.h;
	if (infos->save_map == 1)
	{
		if ((infos->cursor.x >= x && infos->cursor.x <= x + w) &&
			(infos->cursor.y >= y && infos->cursor.y <= y + h) &&
				infos->keys.left_click == 1)
				{
					ft_putendl("ouais 1 ouais");
					infos->edit_button[id].press = 1;
					return (1);
				}
		else if ((infos->cursor.x >= x && infos->cursor.x <= x + w) &&
			(infos->cursor.y >= y && infos->cursor.y <= y + h) &&
				infos->keys.left_click == 0 && infos->edit_button[id].press == 1)
					{
						ft_putendl("ouais 1 ouais");
						return (2);
					}
		else if (((infos->cursor.x < x || infos->cursor.x > x + w) ||
			(infos->cursor.y < y || infos->cursor.y > y + h)) || infos->keys.left_click == 0)
				infos->edit_button[id].press = 0;
	}
	return (0);
}

void	ft_manage_rd_bt(t_window *infos)
{
	int	i;
	int	last_checked;
	int	tmp;

	i = 0;
	tmp = 0;
	while (i < infos->nb_rd_button)
	{
		if (infos->cursor.x >= infos->rd_button[i].x - 7 && infos->cursor.x <= infos->rd_button[i].x + 10 &&
			infos->cursor.y >= infos->rd_button[i].y - 7 && infos->cursor.y <= infos->rd_button[i].y + 10
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

void	ft_print_map(t_window *infos)
{
	int	i;
	int	y;

	y = 10;
	i = 0;
	while (i < infos->nb_rd_button)
	{
		mlx_string_put(infos->mlx_ptr, infos->win_ptr, 30, y, 0xFFFFFF, infos->rd_button[i].data);
		y += 30;
		i++;
	}
}

// void	ft_load_rd_button(t_window *infos)
// {
// 	struct dirent *de;
// 	DIR *dr;
// 	int	count;
// 	t_coord2d	coord;
// 	char	*name;

// 	count = 0;
// 	coord.x = 20;
// 	coord.y = 20;
// 	dr = opendir("maps");
//     if (dr == NULL)
//     {
//         ft_putendl("Could not open current directory");
//         return ;
//     }
// 	while ((de = readdir(dr)) != NULL)
// 		count++;
// 	count -= 2;
// 	closedir(dr);
// 	if (!(infos->rd_button = malloc(sizeof(t_rd_button*) * count)))
// 		return ;
// 	infos->nb_rd_button = count;
// 	count = 0;
// 	dr = opendir("maps");
// 	 if (dr == NULL)
//     {
//         ft_putendl("Could not open current directory");
//         return ;
//     }
// 	while ((de = readdir(dr)) != NULL)
// 	{
// 		count++;
// 		if (count > 2)
// 		{
// 			infos->rd_button[count - 3].x = coord.x;
// 			infos->rd_button[count - 3].y = coord.y;
// 			infos->rd_button[count - 3].checked = 0;
// 			if (!(infos->rd_button[count - 3].data = malloc(sizeof(char) * ft_strlen(de->d_name))))
// 				return ;
// 			infos->rd_button[count - 3].data = ft_strcpy(infos->rd_button[count - 3].data, de->d_name);
// 			name = ft_strjoin("maps/", de->d_name);
// 			if (ft_strcmp(name, infos->map.name) == 0)
// 				infos->rd_button[count - 3].checked = 1;
// 			free(name);
// 			coord.y += 30;
// 		}
// 	}
// 	closedir(dr);
// }

void	ft_load_rd_button(t_window *infos)
{
	int	fd;
	char	*line;
	int		size;
	int		i;
	t_coord2d	coord;
	char		*name;

	i = 0;
	coord.x = 20;
	coord.y = 20;
	fd = open("maps.txt", O_RDONLY);
	if (get_next_line(fd, &line) <= 0)
		return ;
	size = ft_atoi(line);
	infos->nb_rd_button = size;
	free(line);
	if (!(infos->rd_button = malloc(sizeof(t_rd_button) * (size + 1))))
		return ;
	while (get_next_line(fd, &line) > 0)
	{
		printf("i = %d\n", i);
		infos->rd_button[i].x = coord.x;
		infos->rd_button[i].y = coord.y;
		infos->rd_button[i].checked = 0;
		if (!(infos->rd_button[i].data = malloc(sizeof(char) * ft_strlen(line))))
				return ;
		infos->rd_button[i].data = ft_strcpy(infos->rd_button[i].data, line);
		name = ft_strjoin("maps/", line);
		if (ft_strcmp(name, infos->map.name) == 0)
				infos->rd_button[i].checked = 1;
		free(name);
		free(line);
		coord.y += 30;
		i++;
	}
	// ft_putendl("avant le close");
	close(fd);
	// ft_putendl("apres le close");
}