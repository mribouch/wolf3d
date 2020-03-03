/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 07:45:20 by mribouch          #+#    #+#             */
/*   Updated: 2020/03/03 15:17:26 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static int	ft_get_num(char *line, int i)
{
	int	size;
	int	mult;
	int	tmp;
	int	j;
	int	num;

	tmp = i;
	j = 0;
	size = 0;
	mult = 1;
	while (line[tmp++] >= 48 && line[i] <= 57)
		size++;
	j = size;
	while (j-- > 1)
		mult *= 10;
	num = (line[i++] - 48) * mult;
	mult /= 10;
	j = 0;
	while (j++ < size - 1)
	{
		tmp = (line[i++] - 48) * mult;
		num += tmp;
		mult /= 10;
	}
	return (num);
}

int			*ft_get_line(char *line, int width)
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
		else if (line[i] == ' ')
			i++;
		else if (line[i] < 48 || line[i] > 57)
			return (0);
	}
	return (tab);
}

static void	ft_quit_wrong_map(t_window *infos, int fd)
{
	close(fd);
	ft_putendl("Wrong format file !");
	ft_free_rd_button(infos);
	ft_free_button(infos);
	ft_free_texture(infos);
	mlx_destroy_image(infos->mlx_ptr, infos->game.img_ptr);
	mlx_destroy_window(infos->mlx_ptr, infos->win_ptr);
	free(infos);
	exit(0);
}

void		ft_check_map(t_window *infos)
{
	int		i;
	char	*map;
	int		fd;

	i = 0;
	while (i < infos->nb_rd_button)
	{
		if (infos->rd_button[i].checked == 1)
		{
			map = ft_strjoin("maps/", infos->rd_button[i].data);
			if (ft_strcmp(map, infos->map.name) != 0)
			{
				fd = open(map, O_RDONLY);
				ft_free_map(infos);
				infos->map.name = map;
				if ((infos->map.map = ft_get_map(fd, infos)) == 0)
					ft_quit_wrong_map(infos, fd);
				close(fd);
			}
			free(map);
		}
		i++;
	}
}
