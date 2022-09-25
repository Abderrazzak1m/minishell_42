/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiski <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:33:47 by amiski            #+#    #+#             */
/*   Updated: 2021/11/16 13:25:14 by amiski           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*alist;
	t_list	*l;

	alist = *lst;
	while (alist)
	{
		l = alist;
		del(l->content);
		alist = alist->next;
		free(l);
	}
	*lst = NULL;
}
