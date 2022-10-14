/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 19:47:39 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/10/13 23:14:10 by amiski           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

t_token	*new_token(char *val, int type)
{
	t_token	*new_t;

	new_t = malloc(sizeof(t_token));
	if (!new_t)
		return (NULL);
	new_t->next = NULL;
	new_t->prev = NULL;
	new_t->type = type;
	new_t->val = val;
	return (new_t);
}

int	append(t_token **tokens, t_token *newtoken)
{
	t_token	*last;

	last = *tokens;
	if (!newtoken)
		return (0);
	if (!(*tokens))
	{
		*tokens = newtoken;
		return (1);
	}
	while (last->next)
		last = last->next;
	last->next = newtoken;
	newtoken->prev = last;
	return (1);
}

void	clean_tokens(t_token **tokens)
{
	t_token	*forfree;

	while ((*tokens))
	{
		forfree = *tokens;
		*tokens = (*tokens)->next;
		free(forfree);
	}
}
