/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 20:02:32 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/09/27 00:06:57 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include <limits.h>

char *ft_cwd()
{
	char str[1024];
	getcwd(str,1024);
	return (ft_strdup(str));
}
void	ft_pwd(char **cmnd)
{

	if (!cmnd[1])
		printf("%s\n", ft_cwd());
	else
		ft_putendl_fd("too many argument", 2);	
	
}