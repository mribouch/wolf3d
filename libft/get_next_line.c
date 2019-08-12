/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 15:50:08 by mribouch          #+#    #+#             */
/*   Updated: 2019/04/17 20:05:15 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static int	ft_search_nl(char *stock)
{
	int i;

	i = 0;
	if (!stock)
		return (0);
	while (stock[i] != '\n' && stock[i] != '\0')
		i++;
	return (i);
}

static int	ft_other_line(char *stock)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (stock[i] != '\n' && stock[i] != '\0')
		i++;
	while (stock[i] != '\0')
	{
		i++;
		j++;
	}
	return (j);
}

static int	ft_fill_line(char **line, char **stock, int fd, char *tmp)
{
	*line = ft_strsub(stock[fd], 0, ft_search_nl(stock[fd]));
	tmp = stock[fd];
	stock[fd] = ft_strsub(stock[fd], ft_search_nl(stock[fd]) + 1,
			ft_other_line(stock[fd]));
	free(tmp);
	if (stock[fd] == NULL)
		ft_strdel(&stock[fd]);
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	static char	*stock[1];
	char		buff[BUFF_SIZE + 1];
	int			nbr;
	char		*tmp;

	if (fd < 0 || line == NULL || read(fd, buff, 0) < 0)
		return (-1);
	if (stock[fd] == 0)
		stock[fd] = ft_strnew(1);
	if (!stock[fd])
		return (-1);
	while ((nbr = read(fd, buff, BUFF_SIZE)) > 0)
	{
		tmp = stock[fd];
		buff[nbr] = '\0';
		stock[fd] = ft_strjoin(stock[fd], buff);
		free(tmp);
		if (ft_other_line(stock[fd]) > 0)
			return (ft_fill_line(line, stock, fd, tmp));
	}
	if (nbr < 0)
		return (-1);
	if (nbr == 0 && ft_strlen(stock[fd]))
		return (ft_fill_line(line, stock, fd, tmp));
	return (0);
}
