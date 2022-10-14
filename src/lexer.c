/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiski <amiski@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 17:37:34 by amiski            #+#    #+#             */
/*   Updated: 2022/10/13 23:05:08 by amiski           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

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
		write(2, "UNCLOSED QUOT\n", 14);
		return ;
	}
	while (line[i])
	{
		i += check_ws(&line[i], tokens);
		i += is_word(&line[i], tokens, " \t\r\n\"'\v\f|<>$");
		i += is_red(&line[i], tokens);
		i += is_pipe(&line[i], tokens);
		i += is_sign(&line[i], tokens);
		i += is_squot(&line[i], tokens);
		i += is_dquot(&line[i], tokens);
	}
}
