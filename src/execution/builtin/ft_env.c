/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiski <amiski@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 00:07:08 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/10/20 12:13:11 by amiski           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_ev(void)
{
	get_env();
}

void	handler_c_herd(int sig)
{
	(void)sig;
	g_tools.exither = 1;
	rl_done = 1;
}

int	event(void)
{
	return (0);
}
