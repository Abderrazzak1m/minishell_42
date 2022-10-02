/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiski <amiski@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 19:51:11 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/10/02 16:18:33 by amiski           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"


t_env	*ft_delete_head(char *value)
{
	t_env *tmp;
	tmp = g_tools.g_env;
	if(!check_env_value(value))
	{
		tmp = tmp->next;
	}
		
	
	return (tmp);
}
t_env	*delete_in_env(char *value)
{
	t_env *tmp;
	t_env *prv;
	t_env *list;

	tmp = g_tools.g_env;
	prv = g_tools.g_env;
	list = g_tools.g_env;
	tmp = tmp->next;
	tmp = list->next;
	prv = list;
	while (tmp)
	{
	
		if(!ft_strncmp(tmp->variable, value, ft_strlen(tmp->variable) + 1))
		{
			prv->next = tmp->next;
			break ;
		}
		tmp = tmp->next;
		prv = prv->next;
	}
	return (list);
}

void ft_unset(char **cmd)
{
	if (!cmd)
		return ;
	// g_tools.g_env = ft_delete_head(*cmd);
	while (*cmd)
		g_tools.g_env =	delete_in_env(*cmd++);
	
	// get_env();
}