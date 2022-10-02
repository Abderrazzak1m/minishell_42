#include "../../include/minishell.h"


char **get_path(t_env *env)
{
	char **path;
	
	while(env)
	{
		if(ft_strncmp("PATH", env->variable, 4) == 0)
		{
			path = ft_split(env->value+5, ':');
			return(path);
		}
		env = env->next;
	}
	return(NULL);
}

int is_executable(char **path, t_cmd *cmd, char **env)
{
	char *str;
	str = ft_strjoin("/", cmd->cmnd[0]);
	while(*path)
	{
		if(access(ft_strjoin(*path, str), F_OK | X_OK) == 0)
		{
			if (cmd->prev)
				close(cmd->prev->pipe[1]);
			if (cmd->next)
				close(cmd->pipe[0]);
			execve(ft_strjoin(*path, str),cmd->cmnd, env);
			return(1);
		}
		path++;
	}
	return(0);
}

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

void run_cmd(t_cmd *cmd, t_env *env, char **envr)
{
	char **path;
	int pid = fork();
	if(pid == 0)
	{	
		path = get_path(env);
		if(!ft_check_is_builtin(cmd->cmnd))
		{
		if(!is_executable(path, cmd, envr))
			printf("command not fond\n");
		}
		return ;
	}
	
}
void ft_exuc_command(t_cmd *cmd, t_token *token, t_env *env, char **envr)
{
	(void)token;
	int fd[2] ;

    fd[1] = dup(1);
    fd[0] = dup(0);
	while(cmd)
	{
		if(reset_io(cmd))
		{
			run_cmd(cmd,env, envr);
			dup2(fd[1], 1);
			dup2(fd[0], 0);
		}
		cmd = cmd->next;
	}
	close(fd[1]);
	close(fd[0]);
	while(1)
	{
		if (waitpid(-1, NULL, 0) == -1)
			break;
	}
}
