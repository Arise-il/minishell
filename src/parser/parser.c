/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouhlale <oouhlale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:03:44 by oouhlale          #+#    #+#             */
/*   Updated: 2025/07/03 15:18:02 by oouhlale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*parse_input(char *input, t_env *env, int last_exit_status)
{
	t_token	*tokens;
	t_cmd	*cmd_list;

	tokens = tokenize_input(input);
	if (!tokens)
		return (NULL);
	expand_tokens(&tokens, env, last_exit_status);
	if (check_syntax(tokens))
		return (NULL);
	cmd_list = build_command_table(tokens, env, last_exit_status);
	return (cmd_list);
}
