/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 20:38:52 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/09/28 12:54:11 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
# include <termios.h>
# include <fcntl.h>
# include <sys/types.h>
# include <dirent.h>
# include <errno.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/stat.h>
# include <unistd.h>
# include "../libft/libft.h"
//colors
#define S_QUOT '\''
#define D_QUOT '"'
#define SC_S "%'()*+,-./:\^`|~$"
#define SC  " \t\n!\"%'()*+,-./\\:;<=>?@[]^`|$"
#define NOTWORD " \t\r\n\"'\v\f|<>$/"
# define WSPACE -1           // ' '
# define PIPE -2             // |
# define REDIN -3            // <
# define REDOUT -4           // >
# define APPEND -5           // >>
# define HEREDOC -6          // <<
# define SIGN -7             // $
# define EXIT_STATUS -8     // $?
# define WORD -9

typedef struct  s_env
{
  char          *variable;
  char          *value;
  struct s_env  *next;
  struct s_env  *prev;
} t_env;

typedef struct s_globals
{
	t_env		*g_env;
	int			status_sign;
	int			shlvl;
    int         dup_out;
    int         dup_in;
    int         w_out;
    int         r_in;
}	t_globals;

extern t_globals	g_tools;
typedef struct s_token
{
    char *val;
    int type;
    struct s_token *next;
    struct s_token *prev;
}   t_token;


typedef struct s_red
{
    int type;
    char *f_name;
    struct s_red *next;
    struct s_red *prev; 
}   t_red;

typedef struct s_cmd
{
    char **cmnd;   
    struct s_red *red;
    struct s_cmd *next;
    struct s_cmd *prev;
}   t_cmd;
//function

void    ft_readline(char **line);
int     check_quot(char *line, char a, char b);
int all_ws(char *line);
int check_ws(char *line, t_token **tokens);
int is_ws(char c);

//lixer
void lexer(char *line, t_token **tokens);
int append(t_token **tokens, t_token *newtoken);
t_token *new_token(char *val, int type);
void clean_tokens(t_token **tokens);

//enverment
void get_env();
void ft_ev(void);
int append_env(t_env **env, t_env *newenv);
t_env *new_env(char *variable, char *value);
void set_env(char **envr);
int check_error_syntax(t_token *token);
char *get_value_of_env(char *value);
int check_env_value(char *var);
void new_value_in_env(char *str, int type);
void update_exit_value_env(char *var, char *value);

void  expand_data(t_token *token);

//redirection
t_red *new_red(int type, char *f_name);
int     append_red(t_red **reds, t_red *newred);
void    clean_reds(t_red **reds);
void ft_open_herdoc(t_token *token);
//in out red
void ft_red_in(char *namefile);
void ft_red_out(char *namefile);

//command
int append_cmnd(t_cmd **cmds, t_cmd *newcmd);
void clean_cmnds(t_cmd **cmds);
t_cmd *new_cmnd(t_red *red, char **cmnd);
int parser(t_cmd **cmd, t_token *tokens);

// ecex
void ft_exuc_command(t_cmd *cmd, t_token *token, char **env);

//builtin
char    *ft_cwd();
void	ft_pwd(char **cmnd);
void ft_export(char **cmnd);
void ft_cd(char **cmd);
void ft_unset(char **cmd);
void ft_exit(char **value_exit);
void ft_echo(char **cmd);



#endif