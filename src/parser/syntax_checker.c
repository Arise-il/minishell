/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghou <iel-ghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 08:48:07 by oouhlale          #+#    #+#             */
/*   Updated: 2025/06/27 19:31:56 by iel-ghou         ###   ########.fr       */
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
	int	heredoc_count = 0;

	last_type = -1;
	while (tokens)
	{
		if (tokens->type == PIPE)
		{
			if (last_type == PIPE || last_type == -1)
				return (write(2, "Unexpected pipe\n", 17));
			if (!tokens->next)
				return (write(2, "syntax error near unexpected token `|'\n", 40));
		}
		else if (tokens->type == REDIR_IN || tokens->type == REDIR_OUT
			|| tokens->type == REDIR_APPEND || tokens->type == HEREDOC)
		{
			if (!tokens->next || tokens->next->type != WORD)
				return (write(2, "Redirection operator must be followed by a valid file or command\n", 66));
			if (tokens->type == HEREDOC)
			{
				heredoc_count++;
				if (heredoc_count > 16)
					return (write(2, "minishell: maximum here-document count exceeded\n", 48));
			}
		}
		last_type = tokens->type;
		tokens = tokens->next;
	}
	return (0);
}

