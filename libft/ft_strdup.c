/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiski <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 09:49:15 by amiski            #+#    #+#             */
/*   Updated: 2021/11/08 09:50:04 by amiski           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

char	*ft_strdup(char *src)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(ft_strlen(src) + 1);
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
