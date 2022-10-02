/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiski <amiski@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 00:14:41 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/10/02 16:18:17 by amiski           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void get_env()
{
	t_env *env;
	env = g_tools.g_env;
	while (env)
	{
		if (ft_strnstr(env->value, "=", ft_strlen(env->variable) + 1))
			printf("%s\n", env->value);
		env = env->next;
	}
}
int check_env_value(char *var)
{
	t_env *env;
	env = g_tools.g_env;
	while (env)
	{
		if (!ft_strncmp(var, env->variable, ft_strlen(var) + 1))
			return (0);
		env = env->next;
	}
	return (1);
}
void update_exit_value_env(char *var, char *value)
{
	t_env *env;
	env = g_tools.g_env;
	while (env)
	{
		if (!ft_strncmp(var, env->variable, ft_strlen(var) + 1))
			env->value = ft_strjoin( env->value, ft_substr(value, ft_strlen(env->variable) +1,ft_strlen(value)));
		env = env->next;
	}
}
void new_value_in_env(char *str, int type)
{
	char *tmp;
	char *var;

	tmp = ft_split(str, '=')[1];
	var = ft_split(str, '=')[0];
	if (type == 1)
	{
		var = ft_substr(var, 0, ft_strlen(var) - 1);
		tmp = ft_strjoin(var, ft_strjoin("=", tmp));
	}
	else
	{
		if (!tmp)
			tmp = ft_split(str, '=')[0];
		else
			tmp = ft_strjoin(var, ft_strjoin("=", tmp));
	}
	append_env(&g_tools.g_env, new_env(var, tmp));
}
void update_in_env(char *str, int type)
{
	char *tmp;
	char *var;

	tmp = ft_split(str, '=')[1];
	var = ft_split(str, '=')[0];
	if (type == 1)
	{
		var = ft_substr(var, 0, ft_strlen(var) - 1);
		tmp = ft_strjoin(var, ft_strjoin("=", tmp));
	}
	else
	{
		if (!tmp)
			return ;
		else
			tmp = ft_strjoin(var, ft_strjoin("=", tmp));
	}
	update_exit_value_env(var, tmp);
}

char *get_value_of_env(char *value)
{
	t_env *env;
	if (!value)
		return (NULL);
	env = g_tools.g_env;
	while (env)
	{
		if (!ft_strncmp(value , env->variable, ft_strlen(value) +1))
			return (ft_strnstr(env->value, "=", ft_strlen(env->value) -  ft_strlen(value) +1 ) + 1);
		env = env->next;
	}
	return (NULL);
}

void add_new_env(char **str)
{
	char *var;
	int stt;
	while (*str)
	{
		var = ft_split(*str, '=')[0];
		if (var[ft_strlen(var) - 1] == '+')
		{
			var = ft_substr(var, 0, ft_strlen(var) - 1);
			stt = 1;
		}
		if (check_env_value(var))
			new_value_in_env(*str, stt);
		else
			update_in_env(*str, stt);
		stt = 0;
		str++;
	}
}

void set_env(char **envr)
{
	t_env *env;
	env = g_tools.g_env;
	char *value;
	char *variable;

	while (*envr)
	{
		variable = *ft_split(*envr, '=');
		value = ft_strjoin(ft_split(*envr, '=')[0], ft_strjoin("=", ft_split(*envr, '=')[1]));
		if (ft_strncmp(variable, "OLDPWD", ft_strlen(variable) + 1))
			append_env(&env, new_env(variable, value));
		envr++;
	}
	g_tools.g_env = env;
	
}

void get_expoted()
{
	t_env *env;
	char *value;
	env = g_tools.g_env;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
	while (env)
	{
		printf("declare -x ");
		if (!ft_strnstr(env->value, "=", ft_strlen(env->variable) + 1))
			printf("%s\n", env->value);
		else
		{
			value = ft_strnstr(env->value, "=", (ft_strlen(env->value)));
			if (!value)
				printf("%s \n", env->variable);
			else
				printf("%s\"%s\" \n", env->variable, value);
		}
		env = env->next;
	}
}
void ft_export(char **cmnd)
{
	if (!cmnd[1])
		get_expoted();
	else
	{
		cmnd++;
		add_new_env(cmnd);
	}
}