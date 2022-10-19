/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiski <amiski@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 23:05:53 by amiski            #+#    #+#             */
/*   Updated: 2022/10/18 23:36:25 by amiski           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		add(&g_tools.garbage, buff);
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
		add(&g_tools.garbage, buff);
		append(tokens, new_token(ft_memcpy(buff, &line[i], 1), SIGN));
		return (2);
	}
	else if (line[i] == '?')
		return (append(tokens, new_token("?", EXIT_STATUS)), 2);
	else if (ft_strchr(SC, line[i]))
	{
		buff = malloc(sizeof(char) * 2);
		add(&g_tools.garbage, buff);
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
			add(&g_tools.garbage, buff);
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
		add(&g_tools.garbage, buff);
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
		add(&g_tools.garbage, buff);
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
