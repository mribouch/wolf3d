/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 12:56:07 by mribouch          #+#    #+#             */
/*   Updated: 2018/11/21 17:10:52 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	k;

	if (*s2 == '\0')
		return ((char*)s1);
	i = 0;
	while (s1[i] != '\0' && i <= n)
	{
		k = 0;
		while (s2[k] == s1[i + k])
		{
			if ((i + k) == n)
				return (NULL);
			if (s2[k + 1] == '\0')
				return ((char *)(s1 + i));
			k++;
		}
		i++;
	}
	return (NULL);
}
