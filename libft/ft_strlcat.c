/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 12:48:30 by mribouch          #+#    #+#             */
/*   Updated: 2019/04/02 14:44:43 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t lend;
	size_t lens;
	size_t i;

	lend = 0;
	lens = 0;
	i = 0;
	while (dest[lend] != '\0')
		lend++;
	while (src[lens] != '\0')
		lens++;
	if (size < lend)
		return (size + lens);
	while (src[i] != '\0' && (lend + i + 1) < size)
	{
		dest[lend + i] = src[i];
		i++;
	}
	dest[lend + i] = '\0';
	return (lend + lens);
}
