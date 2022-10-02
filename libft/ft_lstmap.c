/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiski <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 18:59:11 by amiski            #+#    #+#             */
/*   Updated: 2021/11/16 13:25:57 by amiski           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*alst;
	t_list	*new;

	alst = NULL;
	while (lst)
	{
		new = (t_list *)malloc(sizeof(t_list));
		if (!new)
		{
			ft_lstclear(&alst, del);
			return (NULL);
		}
		new->content = f(lst->content);
		new->next = NULL;
		ft_lstadd_back(&alst, new);
		lst = lst->next;
	}
	return (alst);
}
