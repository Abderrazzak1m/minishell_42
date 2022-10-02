/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiski <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 09:59:55 by amiski            #+#    #+#             */
/*   Updated: 2021/11/11 10:49:27 by amiski           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	len_str(int n)
{
	long	nbr;
	int		len;

	nbr = n;
	len = 0;
	if (nbr < 0)
	{
		nbr = -nbr;
		len++;
	}
	if (nbr >= 0 && nbr <= 9)
	{
		return (len + 1);
	}
	else
		return (1 + len + len_str(nbr / 10));
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	long	nbr;

	len = len_str(n);
	nbr = n;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (0);
	str[len] = '\0';
	if (nbr < 0)
	{
		str[0] = '-';
		nbr = -nbr;
	}
	if (nbr == 0)
	{
		str[0] = '0';
	}
	while (nbr)
	{
		str[--len] = nbr % 10 + '0';
		nbr /= 10;
	}
	return (str);
}
