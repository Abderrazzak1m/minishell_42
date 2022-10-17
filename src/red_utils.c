/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 23:06:51 by amiski            #+#    #+#             */
/*   Updated: 2022/10/17 09:24:29 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

t_red	*new_red(int type, char *f_name)
{
	t_red	*new_t;

	new_t = malloc(sizeof(t_red));
	add(&g_tools.garbage, new_t);
	if (!new_t)
		return (NULL);
	new_t->next = NULL;
	new_t->prev = NULL;
	new_t->type = type;
	new_t->f_name = f_name;
	return (new_t);
}

int	append_red(t_red **reds, t_red *newred)
{
	t_red	*last;

	last = *reds;
	if (!newred)
		return (0);
	if (!(*reds))
	{
		*reds = newred;
		return (1);
	}
	while (last->next)
		last = last->next;
	last->next = newred;
	newred->prev = last;
	return (1);
}

void	clean_reds(t_red **reds)
{
	t_red	*forfree;

	while ((*reds))
	{
		forfree = *reds;
		*reds = (*reds)->next;
		free(forfree);
	}
}

int	is_red(char *line, t_token **tokens)
{
	if (*line == '<' && line[1] == '<')
	{
		append(tokens, new_token("<<", HEREDOC));
		return (2);
	}
	else if (*line == '<')
	{
		append(tokens, new_token("<", REDIN));
		return (1);
	}
	else if (*line == '>' && line[1] == '>')
	{
		append(tokens, new_token(">>", APPEND));
		return (2);
	}
	else if (*line == '>')
	{
		append(tokens, new_token(">", REDOUT));
		return (1);
	}
	return (0);
}
