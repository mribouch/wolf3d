/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 17:22:54 by mribouch          #+#    #+#             */
/*   Updated: 2019/11/05 17:27:30 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

#   include <stdio.h>

void	ft_edit(t_window *infos)
{
	(void)infos;
	char test[4];
	printf("coucou :\n");
	scanf("%s", test);
	printf("ah yo : %s\n", test);
}