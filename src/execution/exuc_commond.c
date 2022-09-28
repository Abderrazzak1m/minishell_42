/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exuc_commond.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 12:32:34 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/09/28 13:04:00 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_check_is_builtin(char **cmnd)
{
	if (!ft_strncmp(*cmnd, "echo", ft_strlen(*cmnd)))
		return (ft_echo(++cmnd), 1);
	if (!ft_strncmp(*cmnd, "cd", ft_strlen(*cmnd)))
		return (ft_cd(cmnd), 1);
	if (!ft_strncmp(*cmnd, "pwd", ft_strlen(*cmnd)))
		return (ft_pwd(cmnd), 1);
	if (!ft_strncmp(*cmnd, "env", ft_strlen(*cmnd)))
		return (ft_ev(), 1);
	if (!ft_strncmp(*cmnd, "export", ft_strlen(*cmnd)))
		return (ft_export(cmnd), 1);
	if (!ft_strncmp(*cmnd, "exit", ft_strlen(*cmnd)))
		return (ft_exit(++cmnd), 1);
	if (!ft_strncmp(*cmnd, "unset", ft_strlen(*cmnd)))
		return (ft_unset(++cmnd), 1);
	return (0);
}

int	ft_check_red(t_red *red)
{
	t_red *file;

	file = red;
	while (file)
	{
		if (file->type == REDOUT)
			ft_red_out(file->f_name);
		file = file->next;
	}
	return (1);
}

void ft_exuc_command(t_cmd *cmd, t_token *token, char **env)
{
	(void) token;
	t_cmd *tmp;
	(void) env;
	tmp = cmd;
	
	while (tmp)
	{
		g_tools.dup_out = dup(1);
		if (tmp->red != NULL)
		{
			g_tools.dup_out = dup(0);
			ft_check_red(tmp->red);
		}
		if (tmp->red == NULL)
		{
			if(!ft_check_is_builtin(tmp->cmnd))
				printf("is commond systeme\n");
		}
		dup2(g_tools.dup_out, 1);
		close(g_tools.dup_out);
		// dup2(g_tools.dup_in, 0);
		// dup2(g_tools.dup_out, 1);
		// close(g_tools.dup_out);
		// close(g_tools.dup_in);
		tmp = tmp->next;
	}
}