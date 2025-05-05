/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouhlale <oouhlale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 08:48:07 by oouhlale          #+#    #+#             */
/*   Updated: 2025/04/29 10:00:22 by oouhlale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_unclosed_quotes(const char *input)
{
	int	in_single_quote;
	int	in_double_quote;

	in_single_quote = 0;
	in_double_quote = 0;
	while (*input)
	{
		if (*input == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (*input == '\"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		input++;
	}
	if (in_single_quote || in_double_quote)
	{
		printf("minishell: syntax error: unclosed quote\n");
		return (1);
	}
	return (0);
}

int	check_syntax(t_token *tokens)
{
	int	last_type;

	last_type = -1;
	while (tokens)
	{
		if (tokens->type == PIPE)
		{
			// Check if pipe is at the beginning or end
			if (last_type == PIPE || last_type == -1)
				return (write(2, "Unexpected pipe at the beginning or after another pipe\n", 57));
			if (!tokens->next)  // If pipe is at the end
				return (write(2, "Unexpected pipe at the end\n", 29));
		}
		else if (tokens->type == REDIR_IN || tokens->type == REDIR_OUT
			|| tokens->type == REDIR_APPEND || tokens->type == HEREDOC)
		{
			// Check if redirection operator is not followed by a valid file or command
			if (!tokens->next || tokens->next->type != WORD)
				return (write(2, "Redirection operator must be followed by a valid file or command\n", 67));
		}
		last_type = tokens->type;
		tokens = tokens->next;
	}
	return (0);  // No errors
}
