/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 13:14:08 by mribouch          #+#    #+#             */
/*   Updated: 2020/01/03 16:45:40 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "callbacks.h"
#include "key.h"


#include <stdio.h>

static int	ft_get_num(char *line, int i)
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

static int	*ft_get_line(char *line, int width)
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

static int	ft_check_width(char *line)
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

int	ft_count_height(int fd)
{
	char	buf;
	int		height;

	height = 0;
	while (read(fd, &buf, 1) != 0)
	{
		if (buf == '\n')
			height++;
	}
	if (buf == '\n')
		height--;
	height++;
	return (height);
}

int	**ft_get_map(int fd, t_window *infos)
{
	char	*line;
	int		**map;
	int		width;
	int		i;

	i = 1;
	infos->map.height = ft_count_height(fd);
	close(fd);
	fd = open(infos->map.name, O_RDONLY);
	if (get_next_line(fd, &line) <= 0)
		return (0);
	ft_putendl("la");
	width = ft_check_width(line);
	infos->map.width = width;
	if (!(map = malloc(sizeof(int*) * (infos->map.height + 1))))
		return (0);
	map[0] = ft_get_line(line, width);
	free(line);
	while (get_next_line(fd, &line) > 0)
	{
		ft_putendl(line);
		if (width != ft_check_width(line))
			return (0);
		map[i] = ft_get_line(line, width);
		free(line);
		i++;
	}
	map[i] = NULL;
	return (map);
}
