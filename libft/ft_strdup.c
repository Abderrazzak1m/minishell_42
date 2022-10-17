/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 09:49:15 by amiski            #+#    #+#             */
/*   Updated: 2022/10/17 10:00:47 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../include/minishell.h"

char	*ft_strdup(char *src)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(ft_strlen(src) + 1);
	add(&g_tools.garbage, str);
	if (str == NULL)
		return (0);
	while (src[i])
	{
		str[i] = src[i];
		i ++;
	}
	str[i] = '\0';
	return (str);
}
