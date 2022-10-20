/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiski <amiski@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:09:37 by amiski            #+#    #+#             */
/*   Updated: 2022/10/19 13:55:24 by amiski           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	next_export(char *var, char *str, int stt)
{
	if (check_env_value(var))
	{
		ft_unset(ft_split(var, ' '));
		new_value_in_env(str, stt);
	}
	else
		update_in_env(str, stt);
}

void	get_env(void)
{
	t_env	*env;

	env = g_tools.g_env;
	while (env)
	{
		if (ft_strnstr(env->value, "=", ft_strlen(env->variable) + 1))
			printf("%s\n", env->value);
		env = env->next;
	}
}

int	check_env_value(char *var)
{
	t_env	*env;

	env = g_tools.g_env;
	while (env)
	{
		if (!ft_strcmp(var, env->variable))
			return (0);
		env = env->next;
	}
	return (1);
}

void	update_exit_value_env(char *var, char *value)
{
	t_env	*env;

	env = g_tools.g_env;
	while (env)
	{
		if (!ft_strcmp(var, env->variable))
			env->value = ft_strjoin(env->value, \
			ft_substr(value, ft_strlen(env->variable) + 1, ft_strlen(value)));
		env = env->next;
	}
}
