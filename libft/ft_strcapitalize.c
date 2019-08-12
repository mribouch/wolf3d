/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 14:24:27 by mribouch          #+#    #+#             */
/*   Updated: 2018/12/11 14:38:43 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcapitalize(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] >= 97 && str[i] <= 122) || (str[i] >= 65
					&& str[i] <= 90) || (str[i] >= 48 && str[i] <= 57))
		{
			if (str[i] >= 97 && str[i] <= 122)
				str[i] = str[i] - 32;
			i++;
			if (str[i] >= 65 && str[i] <= 90)
				str[i] = str[i] + 32;
			i++;
			while ((str[i] >= 97 && str[i] <= 122) || (str[i] >= 65
						&& str[i] <= 90) || (str[i] >= 48 && str[i] <= 57))
			{
				if (str[i] >= 65 && str[i] <= 90)
					str[i] = str[i] + 32;
				i++;
			}
		}
		i++;
	}
	return (str);
}
