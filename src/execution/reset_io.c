#include"../../include/minishell.h"
int put_error(t_red *red)
{
    char *str;
    str = ft_strjoin("MiniShell : ", red->f_name);
    if(red->type == -3 || red->type == -6)
    {
        if(access(red->f_name, F_OK))
            ft_putendl_fd(ft_strjoin(str, ": No such file or directory"), 2);
        else if(access(red->f_name, R_OK))
            ft_putendl_fd(ft_strjoin(str, ": Permission denied"), 2);
    }
    else if(red->type == -4 || red->type == -5)
    {
        if(access(red->f_name, W_OK))
            ft_putendl_fd(ft_strjoin(str, ": Permission denied"), 2);
    }
    return(-1);
}

int duper_red(int fd, int std)
{
      if(fd != std)
    {
        dup2(fd, std);
        close(fd);
    }
    return(fd);
}
int red_input(t_red *red)
{
    int fd;
    fd = 0;
   while(red)
   {
        if(red->type == -3 || red->type == -6)
        {
                if(red->type == -3)
            {
                
                fd = open(red->f_name, O_RDONLY, 777);
                if(fd < 0)
                    return(put_error(red));
            }
            else
            {
                fd = open(red->f_name, O_RDONLY, 777);
               if(fd < 0)
                return(put_error(red));
            }
        }
        red = red->next;
    }
    return(duper_red(fd, 0));
}
int red_output(t_red *red)
{
    int fd;
    fd = 1;
   while(red)
   {
        if(red->type == -4 || red->type == -5)
        {
            if(red->type == -4)
            {   
            
            fd = open(red->f_name, O_RDWR | O_CREAT | O_TRUNC, 777);

            if(fd < 0)
                return(put_error(red));
            }
            else
            {
                fd = open(red->f_name,  O_WRONLY | O_CREAT | O_APPEND, 777);
               if(fd < 0)
                return(put_error(red));
            }
        }
        red = red->next;
    }
    return(duper_red(fd, 1));
}

int  reset_io(t_cmd *cmd)
{
    if( red_output(cmd->red) == -1 || red_input(cmd->red) == -1)
        return(0);
    else
    {
        if(cmd->next)
        {
            pipe(cmd->pipe);
            if(red_output(cmd->red) == 1)
                dup2(cmd->pipe[1], 1);
            close(cmd->pipe[1]);
        }
        if(cmd->prev)
        {
            if(red_input(cmd->red) == 0)
                dup2(cmd->prev->pipe[0], 0);
            close(cmd->prev->pipe[0]);
        }
    }
    return(1);
}