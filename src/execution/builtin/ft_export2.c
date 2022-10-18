/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiski <amiski@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 00:14:41 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/10/18 22:41:28 by amiski           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	new_value_in_env(char *str, int type)
{
	char	*tmp;
	char	*var;

	var = ft_split(str, '=')[0];
	if (ft_strchr(str, '='))
		tmp = ft_strstr(str, "=") + 1;
	else
		tmp = var;
	if (type == 1)
	{
		var = ft_substr(var, 0, ft_strlen(var) - 1);
		tmp = ft_strjoin(var, ft_strjoin("=", tmp));
	}
	else
	{
		if (ft_strchr(str, '='))
			tmp = ft_strjoin(var, ft_strjoin("=", tmp));
	}
	append_env(&g_tools.g_env, new_env(var, tmp));
}

void	update_in_env(char *str, int type)
{
	char	*tmp;
	char	*var;

	if (ft_strchr(str, '='))
		tmp = ft_strstr(str, "=") + 1;
	else
		return ;
	var = ft_split(str, '=')[0];
	if (type == 1)
	{
		var = ft_substr(var, 0, ft_strlen(var) - 1);
		tmp = ft_strjoin(get_value_of_env(var), tmp);
	}
	ft_unset(ft_split(var, ' '));
	new_value_in_env(ft_strjoin(ft_strjoin(var, "="), tmp), 0);
}

char	*get_value_of_env(char *value)
{
	t_env	*env;

	if (!value)
		return (NULL);
	env = g_tools.g_env;
	while (env)
	{
		if (!ft_strcmp(value, env->variable))
		{
			if (!ft_strchr(env->value, '='))
				return (NULL);
			return (ft_strstr(env->value, "=") + 1);
		}	
		env = env->next;
	}
	return (NULL);
}

int	check_error_export(char *str)
{
	int		i;
	char	*smb;
	char	*smb2;

	i = 0;
	smb = ft_strdup("@#!~_)(+*&^%01234567890");
	smb2 = ft_strdup("@#!~_)(*&^%");
	str = *ft_split(str, '=');
	while (smb[i])
	{
		if (smb[i] == str[0])
			return (ft_putendl_fd("error ", 2), 0);
		if (smb2[i] == str[ft_strlen(str) - 1])
			return (ft_putendl_fd("error w", 2), 0);
		i++;
	}
	return (1);
}

void	add_new_env(char **str)
{
	char	*var;
	int		stt;

	while (*str)
	{
		if (!check_error_export(*str))
		{
			str++;
			continue ;
		}
		var = ft_split(*str, '=')[0];
		if (var[ft_strlen(var) - 1] == '+')
		{
			var = ft_substr(var, 0, ft_strlen(var) - 1);
			stt = 1;
		}
		if (check_env_value(var))
		{
			ft_unset(ft_split(var, ' '));
			new_value_in_env(*str, stt);
		}
		else
			update_in_env(*str, stt);
		stt = 0;
		str++;
	}
}
