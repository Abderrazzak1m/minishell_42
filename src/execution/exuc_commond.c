#include "../../include/minishell.h"


void ft_exuc_command(t_cmd *cmd, t_token *token, char **env)
{
	(void) token;
	int pid;
	pid = fork();
	if( pid == 0)
		execve("/bin/ls", cmd->cmnd, env);
	else
		wait(0);

}