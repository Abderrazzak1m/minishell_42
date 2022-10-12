/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiski <amiski@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 21:55:16 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/10/12 19:08:59 by amiski           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int check_is_n(char *str)
{
	int i;

	i = 1;
	if (*str == '-')
	{
		if (!str[i])
			return (1);
		while (str[i])
		{
			if (str[i++] != 'n')
				return (1);
		}
	}
	else
		return (2);
	return (0);
}

void print_not_new_line(char **str)
{
	while (*str)
	{
		printf("%s", *str);
		str++;
		if (*str != NULL)
			printf(" ");
	}
}
void print_without_new_line(char **str)
{
	while (*str)
		printf("%s ", *str++);
	printf("\n");
}

void check_echo(char **cmd)
{
	int is_not_nl;

	is_not_nl = 0;
	if (!check_is_n(*cmd))
	{
		is_not_nl = 1;
		while (*cmd)
		{
			if (check_is_n(*cmd) == 2 || check_is_n(*cmd) == 1)
				break;
			cmd++;
		}
		print_not_new_line(cmd);
	}
	if (!is_not_nl)
		print_without_new_line(cmd);
}

void ft_echo(char **cmd)
{
	if (!*cmd)
	{
		ft_putendl_fd("", 1);
		return;
	}
	check_echo(cmd);
}