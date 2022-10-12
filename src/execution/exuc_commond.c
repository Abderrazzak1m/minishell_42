/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exuc_commond.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiski <amiski@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 17:23:06 by amiski            #+#    #+#             */
/*   Updated: 2022/10/12 19:30:23 by amiski           ###   ########.fr       */
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

char	**get_d_env(void)
{
	t_env	*tmp;
	char	*buff;

	tmp = g_tools.g_env;
	buff = ft_strdup("");
	while (tmp)
	{
		buff = ft_strjoin(buff, ft_strjoin(tmp->value, "\t"));
		tmp = tmp->next;
	}
	return (ft_split(buff, '\t'));
}

int	is_executable(char **path, t_cmd *cmd)
{
	char	*str;

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

int	run_cmd(t_cmd *cmd, t_env *env)
{
	char	**path;
	int		pid;

	if(ft_check_is_builtin(cmd->cmnd))
	{
		g_tools.status_sign = 0;
		return(1);
	}
	pid = fork();
	if (pid < 0)
		return (0);
	if (pid == 0)
	{	
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		path = get_path(env);
		if (ft_strchr(cmd->cmnd[0], '/'))
		{
			puts(cmd->cmnd[0]);
			execve(cmd->cmnd[0], cmd->cmnd, get_d_env());
			exit(126);
		}
		if (!is_executable(path, cmd))
			exit(127);
		
		else
			g_tools.status_sign = 0;
		return (1);
	}
	else
		signal(SIGINT, SIG_IGN);
	return (1);
}

void	ft_exuc_command(t_cmd *cmd, t_token *token, t_env *env)
{
	int	fd[2];
	int	signal_status;

	(void)token;
    fd[1] = dup(1);
    fd[0] = dup(0);
	while (cmd)
	{
		if (reset_io(cmd))
		{
			if (run_cmd(cmd,env) == 0)
			{
				dup2(fd[1], 1);
				dup2(fd[0], 0);
				close(cmd->pipe[0]);
				break ;
			}	
			dup2(fd[1], 1);
			dup2(fd[0], 0);
		}
		cmd = cmd->next;
	}
	close(fd[1]);
	close(fd[0]);
	while (1)
	{
		if (waitpid(-1, &signal_status, 0) == -1)
			break;
	}
	
	if (WIFEXITED(signal_status))
	  g_tools.status_sign=  WEXITSTATUS(signal_status);
	else if(WIFSIGNALED(signal_status))
	{
		g_tools.status_sign = 128 + WTERMSIG(signal_status);
	}
}
