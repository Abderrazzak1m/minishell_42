/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiski <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 23:16:39 by amiski            #+#    #+#             */
/*   Updated: 2022/10/13 23:44:15 by amiski           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*push_red(t_red **red, t_token *tokens)
{
	int		r;
	t_token	*tmp;

	r = 0;
	tmp = tokens;
	while (tokens->type != PIPE && tokens != NULL)
	{
		if (tokens->next == NULL)
			break ;
		if (tokens->type == REDIN || tokens->type == REDOUT \
				|| tokens->type == APPEND || tokens->type == HEREDOC)
		{
			if (tokens->next->type == -1)
				append_red(red, new_red(tokens->type, \
					ft_strdup(tokens->next->next->val)));
			else
				append_red(red, new_red(tokens->type, \
					ft_strdup(tokens->next->val)));
			r++;
		}
		tokens = tokens->next;
	}
	return (tmp);
}

t_token	*push_this(char *line, t_red **red, t_token *tokens, t_cmd **cmd)
{
	char	**cmnd;

	cmnd = ft_split(line, '\t');
	append_cmnd(cmd, new_cmnd(*red, cmnd));
	return (tokens);
}

t_token	*push_cmd(t_cmd **cmd, t_token *tokens)
{
	t_red	*red;
	char	*line;

	red = NULL;
	line = ft_strdup("");
	tokens = push_red(&red, tokens);
	while (tokens->type != PIPE && tokens != NULL)
	{
		if (tokens->type != REDIN && tokens->type != REDOUT \
				&& tokens->type != APPEND && tokens->type != HEREDOC)
			line = ft_strjoin(line, tokens->val);
		else
		{
			if (tokens->next->type != -1)
				tokens = tokens->next;
			else
				tokens = tokens->next->next;
		}
		if (tokens->next == NULL)
			break ;
		tokens = tokens->next;
	}
	return (push_this(line, &red, tokens, cmd));
}

int	parser(t_cmd **cmd, t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type != PIPE)
			tokens = push_cmd(cmd, tokens)->next;
		else
			tokens = tokens->next;
	}
	return (0);
}
