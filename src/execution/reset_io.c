/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiski <amiski@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 17:06:28 by amiski            #+#    #+#             */
/*   Updated: 2022/10/20 11:44:42 by amiski           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	duper_red(int fd, int std)
{
	if (fd != std)
	{
		dup2(fd, std);
		close(fd);
	}
	return (fd);
}

int	red_input(t_red *red)
{
	int	fd;

	fd = 0;
	while (red)
	{
		if (red->type == -3 || red->type == -6)
		{
			if (red->type == -3)
			{
				fd = open(red->f_name, O_RDONLY, 777);
				if (fd < 0)
					return (put_error(red));
			}
			else
			{
				fd = open(red->f_name, O_RDONLY, 777);
				if (fd < 0)
					return (put_error(red));
				unlink(red->f_name);
			}
		}
		red = red->next;
	}
	return (duper_red(fd, 0));
}

int	red_output(t_red *red)
{
	int	fd;

	fd = 1;
	while (red)
	{
		if (red->type == -4 || red->type == -5)
		{
			if (red->type == -4)
			{
				fd = open(red->f_name, O_RDWR | O_CREAT | O_TRUNC, 777);
				if (fd < 0)
					return (put_error(red));
			}
			else
			{
				fd = open(red->f_name, O_WRONLY | O_CREAT | O_APPEND, 777);
				if (fd < 0)
					return (put_error(red));
			}
		}
		red = red->next;
	}
	return (duper_red(fd, 1));
}

int	reset_io(t_cmd *cmd)
{
	int	tmp[2];

	tmp[0] = red_input(cmd->red);
	tmp[1] = red_output(cmd->red);
	if (tmp[0] == -1 || tmp[1] == -1)
		return (0);
	else
	{
		if (cmd->next)
		{
			pipe(cmd->pipe);
			if (tmp[1] == 1)
				dup2(cmd->pipe[1], 1);
			close(cmd->pipe[1]);
		}
		if (cmd->prev)
		{
			if (tmp[0] == 0)
				dup2(cmd->prev->pipe[0], 0);
			close(cmd->prev->pipe[0]);
		}
	}
	return (1);
}
