/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiski <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 23:14:27 by amiski            #+#    #+#             */
/*   Updated: 2021/11/18 15:27:39 by amiski           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*list;

	if (!new)
		return ;
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	list = ft_lstlast(*alst);
	list->next = new;
}
