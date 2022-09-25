/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiski <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 17:43:51 by amiski            #+#    #+#             */
/*   Updated: 2021/11/13 20:58:31 by amiski           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dest, char *src, unsigned int size)
{
	size_t	i;
	size_t	size_dest;
	size_t	size_src;

	size_dest = ft_strlen(dest);
	size_src = ft_strlen(src);
	i = 0;
	if (size <= size_dest)
		return (size + size_src);
	while (src[i] != '\0' && size_dest + i < size - 1)
	{
		dest[size_dest + i] = src[i];
		i++;
	}
	dest[size_dest + i] = '\0';
	return (size_src + size_dest);
}
