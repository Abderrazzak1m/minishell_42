#include "../../include/minishell.h"

int ft_check_is_builtin(char **cmnd)
{
	if (!ft_strncmp(*cmnd, "echo", ft_strlen(*cmnd)))
		return (printf("%s\n", *cmnd), 1);
	if (!ft_strncmp(*cmnd, "cd", ft_strlen(*cmnd)))
		return (ft_cd(cmnd), 1);
	if (!ft_strncmp(*cmnd, "pwd", ft_strlen(*cmnd)))
		return (ft_pwd(cmnd), 1);
	if (!ft_strncmp(*cmnd, "env", ft_strlen(*cmnd)))
		return (ft_ev(), 1);
	if (!ft_strncmp(*cmnd, "export", ft_strlen(*cmnd)))
		return (ft_export(cmnd), 1);
	if (!ft_strncmp(*cmnd, "exit", ft_strlen(*cmnd)))
		return (printf("%s\n", *cmnd), 1);
	if (!ft_strncmp(*cmnd, "unset", ft_strlen(*cmnd)))
		return (printf("%s\n", *cmnd), 1);
	return (0);
}

void ft_exuc_command(t_cmd *cmd, t_token *token, char **env)
{
	(void) token;
	t_cmd *tmp;
	(void) env;
	tmp = cmd;
	
	while (tmp)
	{
	
		if (tmp->red == NULL)
		{
		if(!ft_check_is_builtin(tmp->cmnd))
			printf("is commond systeme\n");
		}
		tmp = tmp->next;

	}
	



	
	// int pid;
	// pid = fork();
	// if( pid == 0)
	// 	execve("/bin/ls", cmd->cmnd, env);
	// else
	// 	wait(0);

}