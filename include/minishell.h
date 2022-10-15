/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiski <amiski@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 20:38:52 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/10/14 16:04:00 by amiski           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <unistd.h>
# include "../libft/libft.h"
# define NAME "minishell :"
# define ERR_PIPE "syntax error near unexpected token `|'"
# define ERR_FILE "syntax error near unexpected token `'"

# define S_QUOT '\''
# define D_QUOT '"'
# define SC_S "\"'"
# define SC  " \t\n!%()*\"'+,-./\\:;<=>?@[]~^`|$"
# define NOTWORD " \t\r\n\"'\v\f|<>$/"
# define WSPACE -1           // ' '
# define PIPE -2             // |
# define REDIN -3            // <
# define REDOUT -4           // >
# define APPEND -5           // >>
# define HEREDOC -6          // <<
# define SIGN -7             // $
# define EXIT_STATUS -8     // $?
# define WORD -9

typedef struct s_env
{
	char			*variable;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_globals
{
	t_env	*g_env;
	int		status_sign;
	int		shlvl;
}	t_globals;

extern t_globals	g_tools;
typedef struct s_token
{
	char			*val;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_red
{
	int				type;
	char			*f_name;
	struct s_red	*next;
	struct s_red	*prev;
}	t_red;

typedef struct s_cmd
{
	char			**cmnd;
	int				pipe[2];
	struct s_red	*red;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

//function
void	ft_readline(char **line);
int		check_quot(char *line, char a, char b);
int		all_ws(char *line);
int		check_ws(char *line, t_token **tokens);
int		is_ws(char c);
//lexer
void	lexer(char *line, t_token **tokens);
int		append(t_token **tokens, t_token *newtoken);
t_token	*new_token(char *val, int type);
void	clean_tokens(t_token **tokens);
int		is_word(char *line, t_token **tokens, char *sc);
int		is_sc(char *line, t_token **tokens);
int		is_sign(char *line, t_token **tokens);
int		is_squot(char *line, t_token **tokens);
int		is_dquot(char *line, t_token **tokens);
int		is_red(char *line, t_token **tokens);
//enverment
void	get_env(void);
void	ft_ev(void);
int		append_env(t_env **env, t_env *newenv);
t_env	*new_env(char *variable, char *value);
void	set_env(char **envr);
int		check_error_syntax(t_token *token);
char	*get_value_of_env(char *value);
int		check_env_value(char *var);
void	new_value_in_env(char *str, int type);
void	update_exit_value_env(char *var, char *value);
void	expand_data(t_token *token);
//redirection
t_red	*new_red(int type, char *f_name);
int		append_red(t_red **reds, t_red *newred);
void	clean_reds(t_red **reds);
//command
int		append_cmnd(t_cmd **cmds, t_cmd *newcmd);
void	clean_cmnds(t_cmd **cmds);
t_cmd	*new_cmnd(t_red *red, char **cmnd);
int		parser(t_cmd **cmd, t_token *tokens);
// ecex
void	ft_exuc_command(t_cmd *cmd, t_token *token, t_env *env);
int		reset_io(t_cmd *cmd);
void	ft_open_herdoc(t_token *tokens);
//builtin
char	*ft_cwd(void);
void	ft_pwd(char **cmnd);
void	ft_export(char **cmnd);
void	ft_cd(char **cmd);
void	ft_unset(char **cmd);
void	ft_exit(char **value_exit);
void	ft_echo(char **cmd);
t_env	*ft_delete_head(char *value);
void	ft_handl_error(char *s1, char *s2, char *s3, int status);
void	print_error(int type, char *str);
void	signal_wait(void);
///export
void	add_new_env(char **str);
int		check_error_export(char *str);
char	*get_value_of_env(char *value);
void	update_in_env(char *str, int type);
void	new_value_in_env(char *str, int type);
void	update_exit_value_env(char *var, char *value);
int		check_env_value(char *var);
void	get_env(void);
//error
int		put_error(t_red *red);
void	signal_wait(void);
void	print_error(int type, char *str);
void	ft_handl_error(char *s1, char *s2, char *s3, int status);
#endif
