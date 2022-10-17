/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 14:11:21 by amiski            #+#    #+#             */
/*   Updated: 2022/10/17 09:27:33 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
#include "../include/minishell.h"
static int	len_debut(char const *set, char const *s1)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (set[j])
	{
		if (s1[i] == set[j])
		{
			i++;
			j = -1;
		}
		j++;
	}
	return (i);
}

static int	len_fin(char const *set, char const *s1)
{
	int	i;
	int	j;

	i = ft_strlen(s1) - 1;
	j = 0;
	while (set[j])
	{
		if (s1[i] == set[j])
		{
			i--;
			j = -1;
		}
		j++;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		j;
	int		len;

	if (!s1)
		return (NULL);
	if (!set)
		return ((char *)s1);
	i = len_debut(set, s1);
	if (s1[i] == '\0')
		return (ft_strdup(""));
	j = len_fin(set, s1);
	len = j - i + 2;
	str = (char *)malloc(sizeof(char) * len);
	add(&g_tools.garbage, str);
	if (!str)
		return (0);
	ft_memmove(str, s1 + i, (j - i + 1));
	ft_bzero(str + (j - i + 1), 1);
	return (str);
}
