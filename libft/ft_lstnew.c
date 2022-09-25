/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiski <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 20:25:22 by amiski            #+#    #+#             */
/*   Updated: 2021/11/13 22:35:08 by amiski           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*alist;

	alist = (t_list *)malloc(sizeof(t_list));
	if (alist != NULL)
	{
		alist->content = content;
		alist->next = NULL;
	}
	return (alist);
}
