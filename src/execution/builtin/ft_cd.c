/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiski <amiski@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 00:41:26 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/10/19 14:09:40 by amiski           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_switch(void)
{
	char	*old;
	char	*new;

	if (check_env_value("OLDPWD"))
	{
		perror("OLDPWD NOT SET");
		return ;
	}
	else
		new = get_value_of_env("OLDPWD");
	if (!check_env_value("PWD"))
		old = get_value_of_env("PWD");
	else
		old = ft_cwd();
	ft_unset(ft_split("OLDPWD", ' '));
	ft_unset(ft_split("PWD", ' '));
	new_value_in_env(ft_strjoin("OLDPWD=", old), 0);
	new_value_in_env(ft_strjoin("PWD=", new), 0);
	chdir(new);
	printf("%s\n", new);
}

void	ft_update_pwd(char *old)
{
	static int	status;

	ft_unset(ft_split("PWD", ' '));
	new_value_in_env(ft_strjoin("PWD=", ft_cwd()), 0);
	if (!status || !check_env_value("OLDPWD"))
	{
		if (!get_value_of_env("OLDPWD") && status)
			return ;
		ft_unset(ft_split("OLDPWD", ' '));
		new_value_in_env(ft_strjoin("OLDPWD=", old), 0);
	}
	status++;
}

void	src_next(char *cmd, char *old)
{
	if (chdir(cmd) == -1)
		perror("");
	ft_update_pwd(old);
}

void	ft_cd(char **cmd)
{
	char	*old;

	old = ft_cwd();
	if (!cmd[1])
	{
		chdir(getenv("HOME"));
		ft_update_pwd(old);
	}
	else
	{
		cmd++;
		if (*cmd[0] == '.' && cmd[0][1] == '\0')
		{
			if (errno == 2)
				ft_handl_error("cd: ", ERR_CD1, ERR_CD2, 0);
			return ;
		}
		else if (*cmd[0] == '-' && cmd[0][1] == '\0')
			ft_switch();
		else
			src_next(*cmd, old);
	}
}
