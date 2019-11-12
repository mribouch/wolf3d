/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_button.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 16:08:48 by mribouch          #+#    #+#             */
/*   Updated: 2019/11/12 16:59:04 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "wolf.h"

#       include <stdio.h>
#   include <dirent.h>

void	ft_manage_rd_bt(t_window *infos)
{
	int	i;
	int	last_checked;
	int	tmp;

	i = 0;
	tmp = 0;
	ft_putendl("ciciciccicici");
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
	ft_putendl("je suis dedans ?");
	while (i < infos->nb_rd_button)
	{
		mlx_string_put(infos->mlx_ptr, infos->win_ptr, 30, y, 0xFFFFFF, infos->rd_button[i].data);
		y += 30;
		i++;
	}
}

void	ft_load_rd_button(t_window *infos)
{
	struct dirent *de;
	DIR *dr;
	int	count;
	t_coord2d	coord;

	count = 0;
	coord.x = 20;
	coord.y = 20;
	dr = opendir("maps");
    if (dr == NULL)
    {
        printf("Could not open current directory");
        return ;
    }
	while ((de = readdir(dr)) != NULL)
		count ++;
	count -= 2;
	closedir(dr);
	if (!(infos->rd_button = malloc(sizeof(t_rd_button*) * count)))
		return ;
	infos->nb_rd_button = count;
	count = 0;
	dr = opendir("maps");
	 if (dr == NULL)
    {
        printf("Could not open current directory");
        return ;
    }
	while ((de = readdir(dr)) != NULL)
	{
		count++;
		if (count > 2)
		{
			// printf("index = %d", count - 3);
			infos->rd_button[count - 3].x = coord.x;
			infos->rd_button[count - 3].y = coord.y;
			infos->rd_button[count - 3].checked = 0;
			if (!(infos->rd_button[count - 3].data = malloc(sizeof(char) * ft_strlen(de->d_name))))
				return ;
			infos->rd_button[count - 3].data = ft_strcpy(infos->rd_button[count - 3].data, de->d_name);
			if (ft_strcmp(ft_strjoin("maps/", de->d_name), infos->map.name) == 0)
				infos->rd_button[count - 3].checked = 1;
			coord.y += 30;
		}
	}
}