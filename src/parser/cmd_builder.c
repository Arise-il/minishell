/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouhlale <oouhlale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 10:53:35 by oouhlale          #+#    #+#             */
/*   Updated: 2025/07/01 14:25:30 by oouhlale         ###   ########.fr       */
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
	cmd->is_interrupted = 0;
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
	new_args = ft_malloc(sizeof(char *) * (i + 2), 1);
	if (!new_args)
		return ;
	i = 0;
	while (cmd->args && cmd->args[i])
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[i] = ft_strdup(arg);
	new_args[i + 1] = NULL;
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

int	is_redirection_type(int type)
{
	return (type == REDIR_IN || type == REDIR_OUT
		|| type == REDIR_APPEND || type == HEREDOC);
}

t_cmd	*build_command_table(t_token *tokens, t_env *env, int last_status)
{
	t_cmd *(cmd_list), *(current_cmd);
	cmd_list = NULL;
	current_cmd = NULL;
	while (tokens)
	{
		if (!current_cmd)
			current_cmd = create_new_cmd();
		if (tokens->type == WORD)
			add_arg(current_cmd, tokens->value);
		else if (is_redirection_type(tokens->type))
		{
			handle_redirection(current_cmd, tokens, env, last_status);
			tokens = tokens->next;
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
