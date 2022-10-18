/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_value.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiski <amiski@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 23:42:25 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/10/18 22:49:52 by amiski           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	expand_val_sign(char **set_value)
{
	if (!check_env_value(*set_value))
	{
		*set_value = ft_strdup(get_value_of_env(*set_value));
		return (1);
	}
	else if (*set_value[0] == '0')
		*set_value = "minishell";
	else if (*set_value[0] >= '1' && *set_value[0] <= '9')
		*set_value = "\0";
	else
		*set_value = "\0";
	return (0);
}

void	ft_wildcard(char **value)
{
	DIR				*dir;
	char			*buff;
	struct dirent	*dp;

	buff = ft_strdup("");
	dir = opendir(ft_cwd());
	if (dir != NULL)
	{
		dp = readdir(dir);
		while (dp)
		{
			if (!ft_strcmp(dp->d_name, ".") || !ft_strcmp(dp->d_name, ".."))
				dp = readdir(dir);
			else
				buff = ft_strjoin(buff, ft_strjoin(dp->d_name, " "));
			dp = readdir(dir);
		}
	}
	*value = buff;
	closedir(dir);
}

void	expand_data(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == SIGN)
			expand_val_sign(&tmp->val);
		if (tmp->type == EXIT_STATUS)
			tmp->val = ft_itoa(g_tools.status_sign);
		if (tmp->type == WORD)
		{
			if (tmp->val[0] == '~' && tmp->val[1] == '\0')
				tmp->val = ft_strdup(getenv("HOME"));
			if (tmp->val[0] == '~' && tmp->val[1] == '/' && tmp->val[2] == '\0')
				tmp->val = ft_strdup(ft_strjoin(getenv("HOME"), "/"));
			if (tmp->val[0] == '*' && tmp->val[1] == '\0')
				ft_wildcard(&tmp->val);
		}
		tmp = tmp->next;
	}
}
