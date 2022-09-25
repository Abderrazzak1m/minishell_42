/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_value.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 23:42:25 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/09/24 23:54:10 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void  expand_data(t_token *token)
{
	t_token *tmp;

	tmp = token;

	while (tmp)
	{
		if (tmp->type == SIGN)
			tmp->val = ft_strdup(get_value_of_env(tmp->val));
		if (tmp->type == WORD)
		{
			if (tmp->val[0] == '~' && tmp->val[1] == '\0')
				tmp->val = ft_strdup(get_value_of_env("HOME"));
			if (tmp->val[0] == '~' && tmp->val[1] == '\\')
				tmp->val = ft_strdup(ft_strjoin("/", get_value_of_env("HOME")));
		}
		tmp = tmp->next;
	}
	
}