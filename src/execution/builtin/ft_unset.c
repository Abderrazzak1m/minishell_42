/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiski <amiski@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 19:51:11 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/10/18 22:39:34 by amiski           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	delete_in_env(char *value, t_env *tmp)
{
	while (tmp)
	{
		if (!ft_strcmp(tmp->variable, value))
		{
			if (tmp->prev == NULL && tmp->next)
			{
				g_tools.g_env = tmp->next;
				g_tools.g_env->prev = NULL;
				break ;
			}
			else if (tmp->prev && tmp->next == NULL)
				tmp->prev->next = NULL;
			else if (!tmp->next && !tmp->prev)
				g_tools.g_env = NULL;
			else
			{
				tmp->prev->next = tmp->next;
				tmp->next->prev = tmp->prev;
			}
			break ;
		}
		tmp = tmp->next;
	}
	add(&g_tools.garbage, tmp);
}

void	ft_unset(char **cmd)
{
	t_env	*tmp;

	tmp = g_tools.g_env;
	add(&g_tools.garbage, tmp);
	if (!cmd)
		return ;
	while (*cmd)
		delete_in_env(*cmd++, tmp);
}
