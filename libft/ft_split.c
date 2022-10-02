/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiski <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 09:10:23 by amiski            #+#    #+#             */
/*   Updated: 2021/11/10 22:01:30 by amiski           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

static char	**ft_errormal(char **tab, int n)
{
	int	i;

	i = 0;
	while (i <= n)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static int	nbrchaine(char const *s, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			len++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (len);
}

static char	**ft_malloc(char **str, char const *s, char c, int n)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (i < n && s[j])
	{
		k = 0;
		while (s[j] && s[j] != c)
		{
			k++;
			j++;
		}
		if (k != 0)
		{
			str[i] = (char *)malloc((k + 1) * sizeof(char));
			if (str[i] == NULL)
				return (ft_errormal(str, i));
			i++;
		}
		j++;
	}
	str[n] = 0;
	return (str);
}

static void	ft_remp(char **str, char const *s, char c, int len)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (i < len && s[j])
	{
		k = 0;
		if (s[j] != c)
		{
			while (s[j] && s[j] != c)
			{
				str[i][k] = s[j];
				j++;
				k++;
			}
			str[i][k] = '\0';
			i++;
		}
		else
			j++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		len;

	if (s == NULL)
		return (0);
	len = nbrchaine(s, c);
	str = (char **)malloc((len + 1) * sizeof(char *));
	if (!str)
		return (0);
	str = ft_malloc(str, s, c, len);
	if (!str)
		return (0);
	ft_remp(str, s, c, len);
	return (str);
}
