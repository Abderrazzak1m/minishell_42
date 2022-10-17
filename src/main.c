/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 20:43:26 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/10/17 10:00:58 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_globals	g_tools = {0};

int	all_ws(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (!is_ws(line[i]))
			return (0);
	}
	return (1);
}
int	main(int ac, char **av, char **envr)
{
	char *line;
	t_token *tokens;
	t_cmd *cmd;

	(void)av;
	(void)envr;
	set_env(envr);
	if (ac != 1)
	{
		printf("Try again");
		return (0);
	}
	while (1)
	{
		ft_readline(&line);
		line = ft_strtrim(line, " ");
		add(&g_tools.garbage,line);
		if (!line || all_ws(line))
		{
			free(line);
			continue ;
		}
		lexer(line, &tokens);
		if (!tokens)
			continue ;
		if (check_error_syntax(tokens) == 404)
		{
			clean_tokens(&tokens);
			continue ;
		}
		ft_open_herdoc(tokens);
		expand_data(tokens);
		parser(&cmd, tokens);
		ft_exuc_command(cmd, tokens, g_tools.g_env);
		free(line);
		clean_cmnds(&cmd);
		clean_tokens(&tokens);
	}
	// rl_clear_history();
	free_all(g_tools.garbage);
}