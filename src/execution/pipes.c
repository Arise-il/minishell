/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghou <iel-ghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 18:06:55 by iel-ghou          #+#    #+#             */
/*   Updated: 2025/06/26 18:44:09 by iel-ghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

void	setup_pipes(t_cmd *cmd, int prev_read_fd, int pipe_fd[2])
{
	if (prev_read_fd != -1)
	{
		dup2(prev_read_fd, STDIN_FILENO);
		close(prev_read_fd);
	}
	if (cmd->pipe_after)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
}

void	close_unused_fds(int *prev_read_fd, t_cmd *cmd, int pipe_fd[2])
{
	if (*prev_read_fd != -1)
	{
		close(*prev_read_fd);
		*prev_read_fd = -1;
	}
	if (cmd->pipe_after)
	{
		close(pipe_fd[1]);
		*prev_read_fd = pipe_fd[0];
	}
}
