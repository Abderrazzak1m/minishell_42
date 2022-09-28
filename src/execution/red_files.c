/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 12:32:25 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/09/28 13:04:08 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void ft_red_in(char *namefile)
{
	printf ("%s\n", namefile);
}

void ft_red_out(char *namefile)
{
	g_tools.w_out = open(namefile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (g_tools.w_out == -1)
		perror("file");
	dup2(g_tools.w_out, 1);
	close(g_tools.w_out);
}