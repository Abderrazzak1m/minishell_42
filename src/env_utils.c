/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 19:42:08 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/09/24 23:41:29 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env *new_env(char *variable, char *value)
{
	t_env *new_t;
	new_t = malloc(sizeof(t_env));
	if (!new_t)
		return (NULL);
	new_t->next = NULL;
	new_t->prev = NULL;
	new_t->variable = variable;
	new_t->value = value;

	return (new_t);
}

int append_env(t_env **env, t_env *newenv)
{
	t_env *last;

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

// void clean_env(t_env **tokens)
// {
//     t_env *forfree;

//     while((*tokens))
//     {
//         forfree = *tokens;
//         *tokens = (*tokens)->next;
//         free(forfree);
//     }
// }
void get_env()
{
	t_env *env;
	env = g_tools.g_env;
	while (env)
	{
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
	// get_env();
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
	char *str[10] = {"hello", "PWD", "fdx+=11111", "fdx+=2", "sss=1", "sjsjs", NULL};
	add_new_env(str);
	// get_env();
}
