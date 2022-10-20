/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exuc_commond.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiski <amiski@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 17:23:06 by amiski            #+#    #+#             */
/*   Updated: 2022/10/19 14:26:47 by amiski           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**get_path(t_env *env)
{
	char	**path;

	while (env)
	{
		if (ft_strncmp("PATH", env->variable, 4) == 0)
		{
			path = ft_split(env->value + 5, ':');
			return (path);
		}
		env = env->next;
	}
	return (NULL);
}

int	is_executable(char **path, t_cmd *cmd)
{
	char	*str;

	if (ft_strchr(cmd->cmnd[0], '/'))
	{
		if (execve(cmd->cmnd[0], cmd->cmnd, get_d_env()) == -1)
			print_error(1, cmd->cmnd[0]);
		return (0);
	}
	str = ft_strjoin("/", cmd->cmnd[0]);
	while (*path)
	{
		if (access(ft_strjoin(*path, str), F_OK | X_OK) == 0)
		{
			if (cmd->prev)
				close(cmd->prev->pipe[1]);
			if (cmd->next)
				close(cmd->pipe[0]);
			execve(ft_strjoin(*path, str), cmd->cmnd, get_d_env());
			return (1);
		}
		path++;
	}
	return (0);
}

int	ft_check_is_builtin(char **cmnd)
{
	if (!cmnd[0])
		return (-1);
	if (!ft_strncmp(*cmnd, "export", ft_strlen(*cmnd)))
		return (ft_export(cmnd), 1);
	if (!ft_strncmp(*cmnd, "exit", ft_strlen(*cmnd)))
		return (ft_exit(++cmnd), 1);
	if (!ft_strncmp(*cmnd, "unset", ft_strlen(*cmnd)))
		return (ft_unset(++cmnd), 1);
	to_lower(&cmnd[0]);
	if (!ft_strncmp(*cmnd, "echo", ft_strlen(*cmnd)))
		return (ft_echo(++cmnd), 1);
	if (!ft_strncmp(*cmnd, "cd", ft_strlen(*cmnd)))
		return (ft_cd(cmnd), 1);
	if (!ft_strncmp(*cmnd, "pwd", ft_strlen(*cmnd)))
		return (ft_pwd(cmnd), 1);
	if (!ft_strncmp(*cmnd, "env", ft_strlen(*cmnd)))
		return (ft_ev(), 1);
	return (0);
}

int	run_cmd(t_cmd *cmd, t_env *env)
{
	char	**path;
	int		pid;

	if (ft_check_is_builtin(cmd->cmnd))
	{
		g_tools.status_sign = 0;
		return (1);
	}
	pid = fork();
	if (pid < 0)
		return (ft_handl_error(NAME, ERR_FORK, "", 1), 0);
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		path = get_path(env);
		if (!is_executable(path, cmd))
			print_error(0, cmd->cmnd[0]);
		else
			g_tools.status_sign = 0;
	}
	else
		signal(SIGINT, SIG_IGN);
	return (1);
}

void	ft_exuc_command(t_cmd *cmd, t_token *token, t_env *env)
{
	int	fd[2];

	(void)token;
	fd[1] = dup(1);
	fd[0] = dup(0);
	while (cmd)
	{
		if (reset_io(cmd))
		{
			if (run_cmd(cmd, env) == 0)
			{
				close(cmd->pipe[0]);
				break ;
			}
		}
		dup2(fd[1], 1);
		dup2(fd[0], 0);
		cmd = cmd->next;
	}
	dup2(fd[1], 1);
	dup2(fd[0], 0);
	close(fd[1]);
	close(fd[0]);
	signal_wait();
}
