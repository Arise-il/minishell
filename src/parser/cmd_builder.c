/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghou <iel-ghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 10:53:35 by oouhlale          #+#    #+#             */
/*   Updated: 2025/06/27 19:38:35 by iel-ghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*create_new_cmd(void)
{
	t_cmd	*cmd;

	cmd = ft_malloc(sizeof(t_cmd), 1);
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->infile_fd = -1;
	cmd->outfile_fd = -1;
	cmd->append = 0;
	cmd->heredoc = 0;
	cmd->redirection_error = 0;
	cmd->pipe_after = 0;
	cmd->next = NULL;
	return (cmd);
}

void	add_arg(t_cmd *cmd, char *arg)
{
	int		i;
	char	**new_args;

	if (!arg || !*arg) // Ignore empty args
		return ;
	i = 0;
	while (cmd->args && cmd->args[i])
		i++;
	new_args = ft_malloc(sizeof(char *) * (i + 2), 1);
	if (!new_args)
		return ;
	i = 0;
	while (cmd->args && cmd->args[i])
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[i] = ft_strdup(arg); // Add the new argument
	new_args[i + 1] = NULL; // NULL terminate
	cmd->args = new_args;
}

void	add_cmd_to_list(t_cmd **cmd_list, t_cmd *new_cmd)
{
	t_cmd	*tmp;

	tmp = *cmd_list;
	if (!tmp)
		*cmd_list = new_cmd;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_cmd;
	}
}

void	handle_redirection(t_cmd *cmd, t_token *token, t_env *env, int last_status)
{
	t_expand_data	expand_data;
	char			*filename;

	if (token->type == REDIR_IN)
	{
		cmd->infile_fd = open(token->next->value, O_RDONLY);
		if (cmd->infile_fd == -1)
		{
			cmd->redirection_error = 1;
			cmd->infile = ft_strdup(token->next->value);
			return ;
		}
		if (cmd->infile_fd != -1)
			close(cmd->infile_fd);
		cmd->infile = ft_strdup(token->next->value);
	}
	else if (token->type == REDIR_OUT)
	{
		cmd->outfile_fd = open(token->next->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (cmd->outfile_fd == -1)
		{
			cmd->redirection_error = 1;
			cmd->outfile = ft_strdup(token->next->value);
			return ;
		}
		if (cmd->outfile_fd != -1)
			close(cmd->outfile_fd);
		cmd->outfile = ft_strdup(token->next->value);
	}
	else if (token->type == REDIR_APPEND)
	{
		cmd->outfile_fd = open(token->next->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (cmd->outfile_fd == -1)
		{
			cmd->redirection_error = 1;
			cmd->outfile = ft_strdup(token->next->value);
			return ;
		}
		if (cmd->outfile_fd != -1)
			close(cmd->outfile_fd);
		cmd->outfile = ft_strdup(token->next->value);
		cmd->append = 1;
	}
	else if (token->type == HEREDOC)
	{
		expand_data.env = env;
		expand_data.last_status = last_status;
		expand_data.str = NULL;
		expand_data.i = NULL;
		cmd->heredoc = 1;
		filename = handle_heredoc(token->next->value, token->next->quoted, &expand_data);
		//printf("%s\n", filename);
		if (filename == NULL)
		{
			cmd->is_interrupted = 1;
			cmd->redirection_error = 1;
			//printf("%d\n", cmd->is_interrupted);
			return ;
		}
		cmd->infile = filename;
	}
}

t_cmd	*build_command_table(t_token *tokens, t_env *env, int last_status)
{
	t_cmd (*cmd_list), (*current_cmd);
	cmd_list = NULL;
	current_cmd = NULL;
	while (tokens)
	{
		if (!current_cmd)
			current_cmd = create_new_cmd();
		if (tokens->type == WORD)
			add_arg(current_cmd, tokens->value);
		else if (tokens->type == REDIR_IN || tokens->type == REDIR_OUT
			|| tokens->type == REDIR_APPEND || tokens->type == HEREDOC)
		{
			handle_redirection(current_cmd, tokens, env, last_status);
			tokens = tokens->next; // Skip filename token
		}
		else if (tokens->type == PIPE)
		{
			current_cmd->pipe_after = 1;
			add_cmd_to_list(&cmd_list, current_cmd);
			current_cmd = NULL;
		}
		tokens = tokens->next;
	}
	if (current_cmd)
		add_cmd_to_list(&cmd_list, current_cmd);
	return (cmd_list);
}
