/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiski <amiski@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 17:37:34 by amiski            #+#    #+#             */
/*   Updated: 2022/10/12 18:18:53 by amiski           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

int	is_word(char *line, t_token **tokens, char *sc)
{
	int		i;
	char	*buff;

	i = 0;
	if (!ft_strchr(sc, line[i]))
	{
		while (!ft_strchr(sc, line[i]))
			i++;
		buff = malloc(sizeof(char) * i + 1);
		ft_strlcpy(buff, line, i + 1);
		append(tokens, new_token(buff, WORD));
		return (i);
	}
	return (0);
}

int	is_sc(char *line, t_token **tokens)
{
	char	*buff;
	int		i;

	i = -1;
	if (ft_strchr(SC_S, line[++i]))
		return (1);
	if (ft_isdigit(line[i]))
	{
		buff = malloc(sizeof(char) * 2);
		append(tokens, new_token(ft_memcpy(buff, &line[i], 1), SIGN));
		return (2);
	}
	else if (line[i] == '?')
	{
		append(tokens, new_token("?", EXIT_STATUS));
		return (2);
	}
	else if (ft_strchr(SC, line[i]))
	{
		buff = malloc(sizeof(char) * 2);
		append(tokens, new_token(ft_memcpy(buff, &line[i - 1], 2), WORD));
		return (2);
	}
	else
		return (1);
}

int	is_sign(char *line, t_token **tokens)
{
	int		i;
	char	*buff;

	i = 0;
	if (line[i++] == '$')
	{
		if (ft_strchr(SC_S, line[i]) || ft_isdigit(line[i]) || \
			line[i] == '?' || ft_strchr(SC, line[i]) || line[i] == '\'')
			return (is_sc(&line[i], tokens));
		else
		{
			while (!ft_strchr(SC, line[i]))
				i++;
			buff = malloc(sizeof(char) * i + 1);
			ft_strlcpy(buff, line + 1, i);
			append(tokens, new_token(buff, SIGN));
			return (i);
		}
	}
	return (0);
}

int	is_squot(char *line, t_token **tokens)
{
	int		i;
	char	*buff;

	i = 0;
	if (line[i] == '\'')
	{
		while (line[++i] != '\'')
			;
		buff = malloc(sizeof(char) * (i - 1));
		buff[i - 1] = 0;
		append(tokens, new_token(ft_memcpy(buff, &line[1], i - 1), WORD));
		return (i + 1);
	}
	return (0);
}

int	is_dquot(char *line, t_token **tokens)
{
	char	*buff;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (line[i] == '\"')
	{
		while (line[++i] != '\"')
			;
		buff = malloc(sizeof(char) * i);
		buff = ft_memcpy(buff, &line[1], i - 1);
		buff[i - 1] = 0;
		while (buff[j])
		{
			j += is_word(&buff[j], tokens, "\"$");
			j += is_sign(&buff[j], tokens);
		}
		return (i + 1);
	}
	return (0);
}

int	is_red(char *line, t_token **tokens)
{
	if (*line == '<' && line[1] == '<')
	{
		append(tokens, new_token("<<", HEREDOC));
		return (2);
	}
	else if (*line == '<')
	{
		append(tokens, new_token("<", REDIN));
		return (1);
	}
	else if (*line == '>' && line[1] == '>')
	{
		append(tokens, new_token(">>", APPEND));
		return (2);
	}
	else if (*line == '>')
	{
		append(tokens, new_token(">", REDOUT));
		return (1);
	}
	return (0);
}

int	is_pipe(char *line, t_token **tokens)
{
	if (*line == '|')
	{
		append(tokens, new_token("|", PIPE));
		return (1);
	}
	return (0);
}

int	is_ws(char c)
{
	if (c == 32 || (c >= 9 && c <= 15))
		return (1);
	return (0);
}

int	check_ws(char *line, t_token **tokens)
{
	int	i;
	int	r;

	i = -1;
	r = 0;
	while (line[++i] && is_ws(line[i]))
		r++;
	if (r > 0)
	{
		append(tokens, new_token("\t", WSPACE));
		return (i);
	}
	return (0);
}

int	check_quot(char *line, char a, char b)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == b)
			while (line[++i] != b)
				if (!line[i])
					return (0);
		if (line[i] == a)
		{
			while (line[++i] != a && line[i])
				;
			if (line[i] != a)
				return (0);
		}
	}
	return (1);
}

void	lexer(char *line, t_token **tokens)
{
	int	i;

	i = 0;
	if (!check_quot(line, S_QUOT, D_QUOT))
	{
		write(2,"UNCLOSED QUOT\n", 14);
		return ;
	}
	while (line[i])
	{
		i += check_ws(&line[i], tokens);
		i += is_word(&line[i],tokens, " \t\r\n\"'\v\f|<>$");
		i += is_red(&line[i], tokens);
		i += is_pipe(&line[i], tokens);
		i += is_sign(&line[i], tokens);
		i += is_squot(&line[i], tokens);
		i += is_dquot(&line[i], tokens);
	}
}
