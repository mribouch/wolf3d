/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 13:14:08 by mribouch          #+#    #+#             */
/*   Updated: 2020/03/03 15:06:46 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static int	ft_check_width(t_window *infos, char *line, int it)
{
	int	i;
	int	width;

	i = 0;
	width = 0;
	while (line[i] != '\0')
	{
		if (line[i] >= 48 && line[i] <= 55)
		{
			width++;
			if ((it == 0 && line[i] <= 48) || (it == infos->map.height - 1 &&
				line[i] <= 48) || (i == 0 && line[i] <= 48))
				return (0);
			while (line[i] >= 48 && line[i] <= 57)
				i++;
		}
		else if (line[i] == ' ')
			i++;
		else
			return (0);
	}
	i--;
	if (line[i] <= 48)
		return (0);
	return (width);
}

static int	ft_count_height(int fd)
{
	char	buf;
	int		height;
	int		res;

	height = 0;
	while ((res = read(fd, &buf, 1)) != 0)
	{
		if (res < 0 || ((buf < '0' || buf > '8') && buf != ' ' && buf != '\n'))
		{
			ft_putendl("Wrong format file !");
			exit(0);
		}
		if (buf == '\n')
			height++;
	}
	if (buf == '\n')
		height--;
	height++;
	return (height);
}

static void	ft_free_fail(int **map, int count, char *line)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(map[i]);
		i++;
	}
	free(map);
	free(line);
}

static int	ft_iter_line(int **map, int fd, char *line, t_window *infos)
{
	int	count;
	int	i;

	count = 1;
	i = 1;
	while (get_next_line(fd, &line) > 0)
	{
		if (infos->map.width != ft_check_width(infos, line, i) ||
			ft_check_width(infos, line, i) == 0)
		{
			ft_free_fail(map, count, line);
			return (0);
		}
		map[i] = ft_get_line(line, infos->map.width);
		free(line);
		i++;
		count++;
	}
	map[i] = NULL;
	return (1);
}

int			**ft_get_map(int fd, t_window *infos)
{
	char	*line;
	int		**map;
	int		width;

	if (fd < 0)
		return (0);
	infos->map.height = ft_count_height(fd);
	close(fd);
	fd = open(infos->map.name, O_RDONLY);
	if (get_next_line(fd, &line) <= 0)
		return (0);
	if ((width = ft_check_width(infos, line, 0)) == 0)
	{
		free(line);
		return (0);
	}
	infos->map.width = width;
	if (!(map = malloc(sizeof(int*) * (infos->map.height + 1))))
		return (0);
	map[0] = ft_get_line(line, width);
	free(line);
	if (ft_iter_line(map, fd, line, infos) == 0)
		return (0);
	return (map);
}
