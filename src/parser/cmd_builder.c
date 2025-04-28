/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouhlale <oouhlale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 10:53:35 by oouhlale          #+#    #+#             */
/*   Updated: 2025/04/28 10:03:07 by oouhlale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*create_new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->append = 0;
	cmd->heredoc = 0;
	cmd->pipe_after = 0;
	cmd->next = NULL;
	return (cmd);
}

void	add_arg(t_cmd *cmd, char *arg)
{
	int		i;
	char	**new_args;

	if (!arg)
		return ;
	i = 0;
	while (cmd->args && cmd->args[i])
		i++;
	new_args = malloc(sizeof(char *) * (i + 2)); // +1 for new arg, +1 for NULL
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
	free(cmd->args); // Free old array (but not the strings inside)
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

void	handle_redirection(t_cmd *cmd, t_token *token)
{
	if (token->type == REDIR_IN)
		cmd->infile = ft_strdup(token->next->value);
	else if (token->type == REDIR_OUT)
	{
		cmd->outfile = ft_strdup(token->next->value);
		cmd->append = 0;
	}
	else if (token->type == REDIR_APPEND)
	{
		cmd->outfile = ft_strdup(token->next->value);
		cmd->append = 1;
	}
	else if (token->type == HEREDOC)
	{
		cmd->infile = ft_strdup(token->next->value);
		cmd->heredoc = 1;
	}
}

t_cmd	*build_command_table(t_token *tokens)
{
	t_cmd (*cmd_list), (*current_cmd);
	cmd_list = NULL;
	current_cmd = NULL;
	while (tokens)
	{
		if (!current_cmd)
			current_cmd = create_new_cmd(); // malloc + init fields
		if (tokens->type == WORD)
			add_arg(current_cmd, tokens->value);
		else if (tokens->type == REDIR_IN || tokens->type == REDIR_OUT
			|| tokens->type == REDIR_APPEND || tokens->type == HEREDOC)
		{
			handle_redirection(current_cmd, tokens);
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
