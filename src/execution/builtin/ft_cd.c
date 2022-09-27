/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 00:41:26 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/09/27 16:26:56 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void ft_switch()
{
	static int status;
	if(check_env_value("OLDPWD"))
	{
		perror ("OLDPWD NOT SET");
		return ;
	}
	
	if (status == 0)
	{
		if(check_env_value("OLDPWD"))
			new_value_in_env(ft_strjoin("OLDPWD=", ft_cwd()), 0);
		else
			update_exit_value_env("OLDPWD",ft_cwd());
		status = 1;
	}
	else
	{
		status = 0;
	}
}
void ft_update_pwd(char *old)
{
	if(check_env_value("OLDPWD"))
			new_value_in_env(ft_strjoin("OLDPWD=", old), 0);
	else
		update_exit_value_env("OLDPWD", ft_strjoin("OLDPWD=", old));
	if(check_env_value("PWD"))
		new_value_in_env(ft_strjoin("PWD=", ft_cwd()), 0);
	else
		update_exit_value_env("PWD", ft_strjoin("PWD=", ft_cwd()));
	
}

void ft_cd(char **cmd)
{
	char *old;
	old = ft_cwd();
	if(!cmd[1])
	{
		chdir(getenv("HOME"));
		ft_update_pwd(old);
	}
	else
	{
		cmd++;
		if (*cmd[0] == '.' && cmd[0][1] == '\0')
		{
			if (!ft_cwd())
				perror("error");
			return ;
		}
		else if (*cmd[0] == '-' && cmd[0][1] == '\0')
			ft_switch();
		else
		{
			chdir(ft_cwd());
			ft_update_pwd(old);
		}
	}
	
}