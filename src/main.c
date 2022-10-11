/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 20:43:26 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/10/11 13:51:17 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_globals g_tools = {0};
void print_red(t_red *rd)
{
    while (rd)
    {
        printf(" ------------red-----------------\n");
        printf("\tf_name : %s type : %d\n", rd->f_name, rd->type);
        rd = rd->next;
    }
}

void print_cmd(char **tab)
{
    while (*tab)
    {
        printf("%s\n", *tab);
        tab++;
    }
}

int all_ws(char *line)
{
    int i;

    i = -1;
    while (line[++i])
    {
        if (!is_ws(line[i]))
            return (0);
    }
    return (1);
}
int main(int ac, char **av, char **envr)
{
    char *line;
    t_token *tokens;
    t_cmd *cmd;

    (void)av;
    set_env(envr);
    if (ac != 1)
    {
        printf("Try again");
        return (0);
    }
    while (1)
    {

        ft_readline(&line);
        line = ft_strtrim(line, " ");
        if (!line || all_ws(line))
        {
            free(line);
            continue;
        }
        lexer(line, &tokens);
        if (!tokens)
            continue;
        if (check_error_syntax(tokens) == 404)
        {
            clean_tokens(&tokens);
            continue;
        }
        // ft_open_herdoc(tokens);
        expand_data(tokens);
        parser(&cmd, tokens);
        ft_exuc_command(cmd, tokens, g_tools.g_env, envr);
        // while (1);
        
       
        // while(cmd)
        // {
        //     printf("-------------new cmd---------------\n");

        //     print_cmd(cmd->cmnd);
        //     print_red(cmd->red);
        //     cmd = cmd->next;
        // }

        // while(tokens)
        // {
        //     puts("--------------------------");
        //     printf("---value  => %s \n---type  ..=> %d\n",tokens->val, tokens->type);
        //     puts("-------------------------");
        //     tokens = tokens->next;
        // } 
        clean_cmnds(&cmd);
        clean_tokens(&tokens);
    }
}