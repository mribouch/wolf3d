/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 12:57:11 by mribouch          #+#    #+#             */
/*   Updated: 2018/11/21 15:55:19 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s)
{
	char	*str;
	int		len;
	int		i;

	if (s)
	{
		len = ft_strlen(s);
		while (s[len - 1] == ' ' || s[len - 1] == '\n' || s[len - 1] == '\t')
			len--;
		i = -1;
		while (s[++i] == ' ' || s[i] == '\n' || s[i] == '\t')
			len--;
		if (len <= 0)
			len = 0;
		if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
			return (0);
		s = s + i;
		i = -1;
		while (++i < len)
			str[i] = *s++;
		str[i] = '\0';
		return ((char *)str);
	}
	return (NULL);
}
