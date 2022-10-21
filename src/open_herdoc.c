/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_herdoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiski <amiski@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 11:32:39 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/10/21 01:11:32 by amiski           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

int	check__is_exits(char *filename)
{
	DIR				*dir;
	struct dirent	*dp;

	if (!filename)
		return (0);
	dir = opendir("/tmp");
	if (dir != NULL)
	{
		dp = readdir(dir);
		while (dp)
		{
			if (!ft_strcmp(ft_strchr(filename, '.'), dp->d_name))
				return (closedir(dir), 1);
			dp = readdir(dir);
		}
	}
	closedir(dir);
	return (0);
}

char	*get_filename(char *filename)
{
	if (check__is_exits(filename))
		return (get_filename(ft_strjoin(filename, "_c")));
	return (filename);
}

void	opning_line(char **value, int *type)
{
	char		*line;
	char		*buff;
	int			fd;
	static int	id;
	char		*filename;

	signal(SIGINT, handler_c_herd);
	rl_event_hook = event;
	buff = ft_strdup("");
	while (1 && !g_tools.exither)
	{
		line = readline(">");
		add(&g_tools.garbage, line);
		if (!line || !ft_strcmp(line, *value) || g_tools.exither)
			break ;
		buff = ft_strjoin(buff, ft_strjoin(line, "\n"));
	}
	filename = get_filename(ft_strjoin("/tmp/.fileherdooc", ft_itoa(id++)));
	*value = filename;
	fd = open (*value, O_CREAT | O_RDWR | O_TRUNC, 0644);
	*type = WORD;
	ft_putstr_fd(buff, fd);
	close(fd);
}

void	edit_signs(char **value, int type, t_token *token)
{
	t_token	*tmp;
	char	*buff;

	tmp = token;
	buff = ft_strdup("");
	if (type == SIGN || type == WORD || type == EXIT_STATUS)
	{
		while (tmp->type != WSPACE)
		{
			if (tmp->type == WORD)
				buff = ft_strjoin(buff, ft_strjoin("", tmp->val));
			else if (tmp->type == SIGN || tmp->type == EXIT_STATUS)
				buff = ft_strjoin(buff, ft_strjoin("$", tmp->val));
			if (tmp && tmp->type != WSPACE)
			{
				tmp->val = "\t";
				tmp->type = WSPACE;
			}
			if (tmp->next == NULL)
				break ;
			tmp = tmp->next;
		}	
		*value = buff;
	}
}

void	ft_open_herdoc(t_token *token)
{
	while (token)
	{
		if (token->type == HEREDOC)
		{
			if (token->next->type == WSPACE && token->next != NULL)
			{
				edit_signs(&token->next->next->val, token->next->next->type, \
					token->next->next);
				opning_line(&token->next->next->val, &token->next->next->type);
			}
			else
			{
				edit_signs(&token->next->val, token->next->type, token->next);
				opning_line(&token->next->val, &token->next->type);
			}
		}
		token = token->next;
	}
}
