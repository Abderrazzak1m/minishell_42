/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_value.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 23:42:25 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/09/28 13:26:07 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
 
 int	expand_val_sign(char **set_value)
 {
	 printf("%c\n", *set_value[0]);
	 if (!check_env_value(*set_value))
	 {
		*set_value = ft_strdup(get_value_of_env(*set_value));
		return (1);
	}
	else if (*set_value[0] == '0')
		*set_value = "minishell";
	else if (*set_value[0] >= '1' && *set_value[0] <= '9')
		*set_value = "\n\0";
	else
		*set_value = "\0";
	return (0);
 }

 void	ft_wildcard(char **value)
 {
	DIR				*dir;
	char			*buff;

	buff = ft_strdup("");
	struct dirent	*dp;
	dir = opendir(ft_cwd());
	if (dir != NULL)
	{
		dp = readdir(dir);
		while (dp)
		{
			if (!ft_strcmp(dp->d_name, ".") || !ft_strcmp(dp->d_name , ".."))
				dp = readdir(dir);
			else
				buff = ft_strjoin(buff, ft_strjoin(dp->d_name, " "));
			dp = readdir(dir);
		}
	}
	*value = buff;
	closedir(dir);
 }

void  expand_data(t_token *token)
{
	t_token *tmp;

	tmp = token;

	while (tmp)
	{
		if (tmp->type == SIGN)
			expand_val_sign(&tmp->val);
		if (tmp->type == WORD)
		{
			if (tmp->val[0] == '~' && tmp->val[1] == '\0')
				tmp->val = ft_strdup(get_value_of_env("HOME"));
			if (tmp->val[0] == '~' && tmp->val[1] == '/')
				tmp->val = ft_strdup(ft_strjoin(get_value_of_env("HOME"), "/"));
			if (tmp->val[0] == '*' && tmp->val[1] == '\0')
				ft_wildcard(&tmp->val);
		}
		tmp = tmp->next;
	}
	
}