/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 00:14:41 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/10/17 09:52:39 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	add_empty_env(void)
{
	new_value_in_env(ft_strjoin("PWD=", ft_cwd()), 0);
	new_value_in_env(ft_strjoin("SHLVL=", "0"), 0);
}

void	update_shlvl(char *str)
{
	char	*value;

	value = ft_itoa(ft_atoi(str) + 1);
	ft_unset(ft_split("SHLVL", ' '));
	new_value_in_env(ft_strjoin("SHLVL=", value), 0);
}

void	set_env(char **envr)
{
	t_env	*env;
	char	*value;
	char	*variable;

	env = g_tools.g_env;
	if (!*envr)
	{
		add_empty_env();
		update_shlvl(get_value_of_env("SHLVL"));
		return ;
	}
	while (*envr)
	{
		variable = *ft_split(*envr, '=');
		value = ft_strjoin(ft_split(*envr, '=')[0], \
		ft_strjoin("=", ft_split(*envr, '=')[1]));
		if (ft_strncmp(variable, "OLDPWD", ft_strlen(variable) + 1))
			append_env(&env, new_env(variable, value));
		envr++;
	}
	add(&g_tools.garbage, value);
	add(&g_tools.garbage, variable);
	add(&g_tools.garbage, g_tools.g_env);
	g_tools.g_env = env;
	update_shlvl(get_value_of_env("SHLVL"));
}

void	get_expoted(void)
{
	t_env	*env;
	char	*value;

	env = g_tools.g_env;
	while (env)
	{
		printf("declare -x ");
		if (!ft_strnstr(env->value, "=", ft_strlen(env->variable) + 1))
			printf("%s\n", env->value);
		else
		{
			value = ft_strstr(env->value, "=") + 1 ;
			if (!value)
				printf("%s \n", env->variable);
			else
				printf("%s=\"%s\" \n", env->variable, value);
		}
		env = env->next;
	}
}

void	ft_export(char **cmnd)
{
	if (!cmnd[1])
		get_expoted();
	else
	{
		cmnd++;
		add_new_env(cmnd);
	}
}
