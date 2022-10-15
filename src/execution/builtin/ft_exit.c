/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiski <amiski@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 21:17:46 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/10/14 12:48:59 by amiski           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_is_number(char *c)
{
	int	i;

	i = 0;
	if (!c)
		return (0);
	while (c[i])
	{
		if (c[i] < '0' || c[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(char **value_exit)
{
	if (!value_exit[0])
	{
		puts("exit");
		exit (0);
	}
	if (value_exit[1])
	{
		if (!ft_is_number(value_exit[0]))
		{
			puts("bash: exit: ee: numeric argument required");
			exit(255);
		}
	}
	if (ft_is_number(value_exit[0]) && value_exit[1])
		printf("exit\nminishell bash: exit: too many arguments\n");
	else
	{
		puts("exit");
		exit(ft_atoi(value_exit[0]));
	}
}
