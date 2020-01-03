/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 07:45:20 by mribouch          #+#    #+#             */
/*   Updated: 2019/12/04 17:34:27 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void    ft_check_map(t_window *infos)
{
    int i;
    char	*map;
	int		fd;

    i = 0;
	ft_putendl("c'est la que ca fou la merde ?");
    while (i < infos->nb_rd_button)
    {
        if (infos->rd_button[i].checked == 1)
        {
			map = ft_strjoin("maps/", infos->rd_button[i].data);
			// printf("join = %s\n", map);
			// printf("name = %s\n", infos->map.name);
            if (ft_strcmp(map, infos->map.name) != 0)
			{
				fd = open(map, O_RDONLY);
				ft_free_map(infos);
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
	ft_putendl("ah, bah non du coup dsl");
}