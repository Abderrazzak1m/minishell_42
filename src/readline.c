/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiski <amiski@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:23:53 by amiski            #+#    #+#             */
/*   Updated: 2022/10/14 16:23:54 by amiski           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_handel_sig(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_readline(char **line)
{
	signal(SIGINT, ft_handel_sig);
	signal(SIGQUIT, SIG_IGN);
	rl_catch_signals = 0;
	*line = readline("miniShell> ");
	if (!(*line))
	{
		printf("exit\n");
		exit(0);
	}
	if (*line && (*line)[0] && !all_ws(*line))
		add_history(*line);
	return ;
}
