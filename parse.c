/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 13:14:08 by mribouch          #+#    #+#             */
/*   Updated: 2019/08/13 15:31:38 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "callbacks.h"
#include "key.h"


#include <stdio.h>

int	ft_get_num(char *line, int i)
{
	int	size;
	int	mult;
	int	tmp;
	int	j;
	int	tmpsize;
	int	num;

	tmp = i;
	j = 0;
	size = 0;
	mult = 1;
	while (line[tmp++] >= 48 && line[i] <= 57)
		size++;
	tmpsize = size;
	while (tmpsize > 1)
	{
		mult *= 10;
		tmpsize--;
	}
	num = (line[i++] - 48) * mult;
	mult /= 10;
	while (j < size - 1)
	{
		tmp = (line[i++] - 48) * mult;
		num += tmp;
		j++;
		mult /= 10;
	}
	return (num);
}

int	*ft_get_line(char *line, int width)
{
	int	*tab;
	int	num;
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!(tab = malloc(sizeof(int) * (width + 1))))
		return (0);
	while (line[i] != '\0')
	{
		if (line[i] >= 48 && line[i] <= 57)
		{
			num = ft_get_num(line, i);
			tab[j] = num;
			j++;
			while (line[i] >= 48 && line[i] <= 57)
				i++;
		}
		else
			i++;
	}
	return (tab);
}

int	ft_check_width(char *line)
{
	int	i;
	int	width;

	i = 0;
	width = 0;
	while (line[i] != '\0')
	{
		if (line[i] >= 48 && line[i] <= 57)
		{
			width++;
			while (line[i] >= 48 && line[i] <= 57)
				i++;
		}
		else
			i++;
	}
	return (width);
}

int	**ft_get_map(int fd, t_window *infos)
{
	char	*line;
	int		**map;
	int		width;
	int		i;

	i = 1;
	infos->map.height = 1;
	if (get_next_line(fd, &line) <= 0)
		return (0);
	width = ft_check_width(line);
	infos->map.width = width;
	if (!(map = malloc(sizeof(int*) * (width + 1))))
		return (0);
	map[0] = ft_get_line(line, width);
	while (get_next_line(fd, &line) > 0)
	{
		if (width != ft_check_width(line))
			return (0);
		map[i] = ft_get_line(line, width);
		i++;
		infos->map.height++;
	}
	map[i] = NULL;
	return (map);
}
