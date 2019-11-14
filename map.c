/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 07:45:20 by mribouch          #+#    #+#             */
/*   Updated: 2019/11/14 08:30:31 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include        <stdio.h>

void    ft_check_map(t_window *infos)
{
    int i;
    char	*map;
	int		fd;

    i = 0;
	ft_putendl("jooooohn");
    while (i < infos->nb_rd_button)
    {
        if (infos->rd_button[i].checked == 1)
        {
			map = ft_strjoin("maps/", infos->rd_button[i].data);
			printf("join = %s\n", map);
			printf("name = %s\n", infos->map.name);
            if (ft_strcmp(map, infos->map.name) != 0)
			{
				ft_putendl("hammooooooon");
				fd = open(map, O_RDONLY);
				infos->map.name = map;
				if ((infos->map.map = ft_get_map(fd, infos)) == 0)
				{
					ft_putendl("Wrong input ! The lines doesn't have the same lenght !");
					exit(0);
				}
				close(fd);
			}
			free(map);
        }
        i++;
    }
}