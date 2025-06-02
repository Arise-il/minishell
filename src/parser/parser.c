/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouhlale <oouhlale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:03:44 by oouhlale          #+#    #+#             */
/*   Updated: 2025/06/01 16:17:34 by oouhlale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("value: %-15s | type: %d\n", tokens->value, tokens->type);
		tokens = tokens->next;
	}
}

void	print_cmds(t_cmd *cmd)
{
	int i = 1;
	while (cmd)
	{
		printf("------ Command %d ------\n", i++);
		if (cmd->args)
		{
			int j = 0;
			while (cmd->args[j])
			{
				printf("arg[%d]: %s\n", j, cmd->args[j]);
				j++;
			}
		}
		else
			printf("No args\n");

		if (cmd->infile)
			printf("infile: %s\n", cmd->infile);
		if (cmd->outfile)
			printf("outfile: %s\n", cmd->outfile);
		if (cmd->append)
			printf("append mode: >>\n");
		if (cmd->heredoc)
			printf("heredoc mode: <<\n");
		if (cmd->pipe_after)
			printf("pipe to next: yes\n");
		printf("\n");
		cmd = cmd->next;
	}
}


t_cmd	*parse_input(char *input, t_env *env, int last_exit_status)
{
	t_token	*tokens;
	t_cmd	*cmd_list;

	// Step 1: Tokenize input
	tokens = tokenize_input(input);
	if (!tokens)
		return (NULL);
	// Step 2: Expand variables ($VAR, $?, quote removal, etc.)
	expand_tokens(&tokens, env, last_exit_status);
	// Step 3: Syntax checking
	if (check_syntax(tokens))
	{
		//free_tokens(tokens);
		return (NULL);
	}
	// Step 4: Parse tokens into command structs
	cmd_list = build_command_table(tokens, env, last_exit_status);
	// Step 5: Free tokens
	//free_tokens(tokens);
	return (cmd_list);
}
