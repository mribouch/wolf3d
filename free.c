/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 14:08:25 by mribouch          #+#    #+#             */
/*   Updated: 2020/01/07 17:56:28 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	ft_free_texture(t_window *infos)
{
	int	i;

	i = 0;
	while (i < 9)
	{
		if (i < 3)
		{
			ft_putendl("avant le destroy gui");
			mlx_destroy_image(infos->mlx_ptr, infos->gui[i].img_ptr);
			ft_putendl("APRES le destroy gui");
		}
		ft_putendl("avant le destroy tex");
		mlx_destroy_image(infos->mlx_ptr, infos->texture[i].img_ptr);
		ft_putendl("APRES le destroy tex");
		i++;
	}
	free(infos->gui);
	free(infos->texture);
}

void	ft_free_button(t_window *infos)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (i < 2)
		{
			mlx_destroy_image(infos->mlx_ptr, infos->edit_button[i].button_up.img_ptr);
			mlx_destroy_image(infos->mlx_ptr, infos->edit_button[i].button_down.img_ptr);
		}
		ft_putendl("avant le destroy button");
		mlx_destroy_image(infos->mlx_ptr, infos->button[i].button_up.img_ptr);
		mlx_destroy_image(infos->mlx_ptr, infos->button[i].button_down.img_ptr);
		ft_putendl("APRES le destroy button");
		i++;
	}
	free(infos->edit_button);
	free(infos->button);
}

void	ft_free_rd_button(t_window *infos)
{
	int	i;

	i = 0;
	while (i < infos->nb_rd_button)
	{
		ft_putstr("combien = ");
		ft_putnbr(i);
		ft_putchar('\n');
		free(infos->rd_button[i].data);
		i++;
	}
	free(infos->rd_button);
}

void	ft_free_map(t_window *infos)
{
	int	i;

	i = 0;
	ft_putendl("oui je freebien");
	while (i < infos->map.height)
	{
		free(infos->map.map[i]);
		i++;
	}
	free(infos->map.map);
	ft_putendl("fin free map");
	// free(infos->map.name);
}

void	ft_quit_wolf(t_window *infos)
{
	ft_putendl("avat free map");
	ft_free_map(infos);
	ft_putendl("avant free rd_button");
	ft_free_rd_button(infos);
	ft_putendl("avant free button");
	ft_free_button(infos);
	ft_putendl("avant free texture");
	ft_free_texture(infos);
	ft_putendl("avant free solo gui");
	// free(infos->gui);
	ft_putendl("avant free solo tex");
	// free(infos->texture);
	ft_putendl("avant free solo rdbutton");
	// free(infos->rd_button);
	ft_putendl("avant free solo button");
	// free(infos->button);
	mlx_destroy_image(infos->mlx_ptr, infos->game.img_ptr);
	mlx_destroy_window(infos->mlx_ptr, infos->win_ptr);
	free(infos);
}