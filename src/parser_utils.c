/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 23:14:16 by amiski            #+#    #+#             */
/*   Updated: 2022/10/17 09:24:46 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	to_lower(char **str)
{
	int	i;

	i = -1;
	while ((*str)[++i])
	{
		if ((*str)[i] >= 'A' && (*str)[i] <= 'Z')
			(*str)[i] = ft_tolower((*str)[i]);
	}
}

t_cmd	*new_cmnd(t_red *red, char **cmnd)
{
	t_cmd	*new_t;

	new_t = malloc(sizeof(t_cmd));
	add(&g_tools.garbage, new_t);
	if (!new_t)
		return (NULL);
	new_t->next = NULL;
	new_t->prev = NULL;
	new_t->cmnd = cmnd;
	new_t->red = red;
	return (new_t);
}

int	append_cmnd(t_cmd **cmds, t_cmd *newcmd)
{
	t_cmd	*last;

	last = *cmds;
	if (!newcmd)
		return (0);
	if (!(*cmds))
	{
		*cmds = newcmd;
		return (1);
	}
	while (last->next)
		last = last->next;
	last->next = newcmd;
	newcmd->prev = last;
	return (1);
}

void	clean_cmnds(t_cmd **cmds)
{
	t_cmd	*forfree;

	while ((*cmds))
	{
		forfree = *cmds;
		clean_reds(&(*cmds)->red);
		*cmds = (*cmds)->next;
		free(forfree);
	}
}
