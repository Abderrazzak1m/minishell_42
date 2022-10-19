/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiski <amiski@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 19:42:08 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/10/19 01:32:46 by amiski           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**get_d_env(void)
{
	t_env	*tmp;
	char	*buff;

	tmp = g_tools.g_env;
	buff = ft_strdup("");
	while (tmp)
	{
		buff = ft_strjoin(buff, ft_strjoin(tmp->value, "\t"));
		tmp = tmp->next;
	}
	return (ft_split(buff, '\t'));
}

t_env	*new_env(char *variable, char *value)
{
	t_env	*new_t;

	new_t = malloc(sizeof(t_env));
	add(&g_tools.garbage, new_env);
	if (!new_t)
		return (NULL);
	new_t->next = NULL;
	new_t->prev = NULL;
	new_t->variable = variable;
	new_t->value = value;
	return (new_t);
}

int	append_env(t_env **env, t_env *newenv)
{
	t_env	*last;

	last = *env;
	if (!newenv)
		return (0);
	if (!(*env))
	{
		*env = newenv;
		return (1);
	}
	while (last->next)
		last = last->next;
	last->next = newenv;
	newenv->prev = last;
	return (1);
}
