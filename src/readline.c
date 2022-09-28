#include"../include/minishell.h"

void    ft_readline(char **line)
{
    signal(SIGQUIT, SIG_IGN);
    *line = readline("miniShell> ");
    if(!(*line))
    {
        printf("exit\n");
        exit(0);
    }
    if(*line && (*line)[0] && !all_ws(*line))
        add_history(*line);
    return ;
}

