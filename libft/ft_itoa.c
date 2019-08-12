/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 12:42:16 by mribouch          #+#    #+#             */
/*   Updated: 2018/12/11 15:03:14 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	int		sign;
	int		temp_n;
	char	*res;
	size_t	len;

	temp_n = n;
	len = 0;
	if (n < 0)
		sign = -1;
	else
		sign = 1;
	len = 2 + (n < 0);
	while ((temp_n = temp_n / 10))
		len++;
	if (!(res = (char *)malloc(sizeof(char) * (len--))))
		return (0);
	res[len--] = '\0';
	res[len--] = sign * (n % 10) + '0';
	while ((n = n / 10))
		res[len--] = sign * (n % 10) + '0';
	if (sign < 0)
		res[len] = '-';
	return (res);
}
