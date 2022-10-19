/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiski <amiski@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 09:16:06 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/10/18 23:34:30 by amiski           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add(t_node_free **garbage, void *pointer)
{
	t_node_free	*node;

	node = malloc(sizeof(t_node_free));
	if (!node)
		return ;
	node->pointer = pointer;
	node->next = *garbage;
	*garbage = node;
}

void	free_all(t_node_free *garbage)
{
	void	*tmp;

	tmp = NULL;
	while (garbage)
	{
		free(garbage->pointer);
		tmp = garbage;
		garbage = garbage->next;
		free(tmp);
	}
}
