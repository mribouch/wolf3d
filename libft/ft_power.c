/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 12:37:33 by mribouch          #+#    #+#             */
/*   Updated: 2018/12/11 14:40:43 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_power(int n, int pow)
{
	int	i;
	int	temp_n;

	i = 1;
	temp_n = n;
	if (pow > 0)
	{
		while (i < pow)
		{
			temp_n = temp_n * n;
			i++;
		}
		return (temp_n);
	}
	else
		ft_putstr("Rentrez une puissance positive\n");
	return (0);
}
