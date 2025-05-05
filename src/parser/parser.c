/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouhlale <oouhlale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:03:44 by oouhlale          #+#    #+#             */
/*   Updated: 2025/04/29 09:56:20 by oouhlale         ###   ########.fr       */
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

t_cmd	*parse_input(char *input)
{
	t_token *tokens;
	t_cmd   *cmd_list;

	//Tokenize input
	tokens = tokenize_input(input);
	//print_tokens(tokens);
	//Check syntax
	if (check_syntax(tokens))
	{
		free_tokens(tokens);
		return (NULL);
	}
	//Parse tokens into commands
	cmd_list = build_command_table(tokens);
	free_tokens(tokens);
	return (cmd_list);
}
