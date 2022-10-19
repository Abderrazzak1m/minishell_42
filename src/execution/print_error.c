/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiski <amiski@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:05:11 by amiski            #+#    #+#             */
/*   Updated: 2022/10/19 01:12:29 by amiski           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_handl_error(char *s1, char *s2, char *s3, int status)
{
	char	*str;

	g_tools.status_sign = status;
	str = ft_strjoin(s1, ft_strjoin(s2, s3));
	ft_putendl_fd(str, 2);
}

void	print_error(int type, char *str)
{
	if (type == 1)
	{
		if (errno == 13)
		{
			ft_handl_error(NAME, str, ": Permission denied", 126);
			exit(126);
		}
		else
		{
			ft_handl_error(NAME, str, ": No such file or directory", 127);
			exit(127);
		}
	}
	else
	{
		ft_handl_error(NAME, str, ": command not found", 127);
		exit(127);
	}
}

void	signal_wait(void)
{
	int	signal_status;

	while (1)
	{
		if (waitpid(-1, &signal_status, 0) == -1)
			break ;
	}
	if (WIFEXITED(signal_status))
		g_tools.status_sign = WEXITSTATUS(signal_status);
	else if (WIFSIGNALED(signal_status))
	{
		if (WTERMSIG(signal_status) == 2 || WTERMSIG(signal_status) == 3)
		{
			if (WTERMSIG(signal_status) == 2)
				ft_putendl_fd("", 2);
			else
				ft_putendl_fd("QUIT: 3", 2);
			g_tools.status_sign = 128 + WTERMSIG(signal_status);
		}
	}
}

int	put_error(t_red *red)
{
	if (red->type == -3 || red->type == -6)
	{
		if (access(red->f_name, F_OK))
			ft_handl_error("minishell: ", red->f_name, \
				" : No such file or directory", 1);
		else if (access(red->f_name, R_OK))
			ft_handl_error("minishell: ", \
				red->f_name, " : Permission denied", 1);
	}
	else if (red->type == -4 || red->type == -5)
	{
		if (access(red->f_name, W_OK))
			ft_handl_error("minishell: ", red->f_name, \
			" : Permission denied", 1);
	}
	return (-1);
}
