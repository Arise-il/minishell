/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouhlale <oouhlale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:22:09 by oouhlale          #+#    #+#             */
/*   Updated: 2025/07/03 18:53:28 by oouhlale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_infile(t_cmd *cmd, char *filename)
{
	cmd->infile_fd = open(filename, O_RDONLY);
	if (cmd->infile_fd == -1)
	{
		cmd->redirection_error = 1;
		cmd->infile = ft_strdup(filename);
		return ;
	}
	close(cmd->infile_fd);
	cmd->infile = ft_strdup(filename);
}

void	set_outfile(t_cmd *cmd, char *filename, int flags, int append)
{
	cmd->outfile_fd = open(filename, flags, 0644);
	if (cmd->outfile_fd == -1)
	{
		cmd->redirection_error = 1;
		cmd->outfile = ft_strdup(filename);
		return ;
	}
	close(cmd->outfile_fd);
	cmd->outfile = ft_strdup(filename);
	cmd->append = append;
}

void	handle_heredoc_redirect(t_cmd *cmd, t_token *token,
t_env *env, int last_status)
{
	t_expand_data	exp;
	char			*filename;

	exp.env = env;
	exp.last_status = last_status;
	exp.str = NULL;
	exp.i = NULL;
	cmd->heredoc = 1;
	filename = handle_heredoc(token->next->value,
			token->next->quoted, &exp, cmd->is_interrupted);
	if (!filename)
	{
		cmd->is_interrupted = 1;
		cmd->redirection_error = 1;
		return ;
	}
	cmd->infile = filename;
}

void	handle_redirection(t_cmd *cmd, t_token *token, t_env *env,
int last_status)
{
	if (cmd->redirection_error == 1)
		return ;
	if (token->type == REDIR_IN)
		set_infile(cmd, token->next->value);
	else if (token->type == REDIR_OUT)
		set_outfile(cmd, token->next->value, O_CREAT | O_WRONLY | O_TRUNC, 0);
	else if (token->type == REDIR_APPEND)
		set_outfile(cmd, token->next->value, O_CREAT | O_WRONLY | O_APPEND, 1);
	else if (token->type == HEREDOC)
		handle_heredoc_redirect(cmd, token, env, last_status);
}
