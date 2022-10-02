/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 21:56:16 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/09/24 23:26:38 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

size_t check_error_pipe(t_token *token)
{
	int last_pipe;

	if (token->type == PIPE)
		return (ft_putstr_fd("syntax error '|'\n", 2), 404);
	while (token)
	{
		if (token->type == PIPE && token->next != NULL)
		{
			token = token->next;
			if (token->type == WSPACE && token->next != NULL)
				token = token->next;
			if (token->type == PIPE)
				return (ft_putstr_fd("syntax error '||'\n", 2), 404);
		}
		last_pipe = token->type;
		token = token->next;
		if (!token)
		{
			if (last_pipe == -2)
				return (ft_putstr_fd("syntax error fin '|'\n", 2), 404);
		}
	}
	return (1);
}

size_t check_error_rederection(t_token *token)
{
	
	while (token)
	{
		if ((token->type == REDIN || token->type == REDOUT || \
		token->type == HEREDOC || token->type == APPEND ) && token->next == NULL)
			return (ft_putstr_fd("error syntax redirections\n", 2),404);
		if ((token->type == REDIN || token->type == REDOUT || \
		token->type == HEREDOC || token->type == APPEND ) && token->next != NULL)
		{
			token = token->next;
			if (token->type == WSPACE && token->next != NULL)
				token = token->next;
			if (token->type != WORD && token->type != SIGN)
				return (ft_putstr_fd("error syntax redirection\n", 2),404);
		}
		token = token->next;
	}
	return (1);
}
int check_error_syntax(t_token *token)
{
	t_token *cmd;

	cmd = token;
	if (check_error_pipe(cmd) == 404)
		return (404);
	if (check_error_rederection(token) == 404)
		return (404);

		return (1);
}