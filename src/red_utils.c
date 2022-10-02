#include"../include/minishell.h"

t_red *new_red(int type, char *f_name)
{
    t_red *new_t;
    new_t = malloc(sizeof(t_red));
    if(!new_t)
        return(NULL);
    new_t->next = NULL;
    new_t->prev = NULL;
    new_t->type = type;
    new_t->f_name = f_name;
    return(new_t); 
}

int append_red(t_red **reds, t_red *newred)
{
    t_red *last;

    last = *reds;
    if(!newred)
        return(0);
    if(!(*reds))
    {
        *reds = newred;
        return(1);
    }
    while(last->next)
        last = last->next;
    last->next = newred;
    newred->prev = last;
    return(1);
}

void clean_reds(t_red **reds)
{
    t_red *forfree;

    while((*reds))
    {
        forfree = *reds;
        *reds = (*reds)->next;
        free(forfree);
    }
}