/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghou <iel-ghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 18:08:54 by iel-ghou          #+#    #+#             */
/*   Updated: 2025/06/26 18:44:18 by iel-ghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

int	apply_outfile_redir(t_cmd *cmd)
{
	int	fd;

	if (!cmd->outfile)
		return (0);
	if (cmd->append)
		fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(cmd->outfile);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 outfile");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	apply_infile_redir(t_cmd *cmd)
{
	int	fd;

	if (!cmd->infile)
		return (0);
	fd = open(cmd->infile, O_RDONLY);
	if (fd == -1)
	{
		perror(cmd->infile);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2 infile");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	handle_redirection_error(t_cmd *cmd)
{
	if (cmd->infile)
		perror(cmd->infile);
	else
		perror(cmd->outfile);
	return (-1);
}

int	apply_redirections(t_cmd *cmd)
{
	int	ret;

	if (cmd->redirection_error == 1)
		return (handle_redirection_error(cmd));
	ret = apply_infile_redir(cmd);
	if (ret != 0)
		return (ret);
	ret = apply_outfile_redir(cmd);
	return (ret);
}
