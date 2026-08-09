/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouhlale <oouhlale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 08:48:07 by oouhlale          #+#    #+#             */
/*   Updated: 2025/07/03 15:19:58 by oouhlale         ###   ########.fr       */
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

static int	is_invalid_pipe_position(t_token *token, int last_type)
{
	if (token->type == PIPE)
	{
		if (last_type == PIPE || last_type == -1)
			return (write(2, "Unexpected pipe\n", 17));
		if (!token->next)
			return (write(2, "syntax error near unexpected token `|'\n", 40));
	}
	return (0);
}

static int	is_invalid_redirection(t_token *token)
{
	if (token->type == REDIR_IN || token->type == REDIR_OUT
		|| token->type == REDIR_APPEND || token->type == HEREDOC)
	{
		if (!token->next || token->next->type != WORD)
		{
			return (write(2,
					"syntax error near unexpected token `newline'\n",
					46));
		}
	}
	return (0);
}

static int	handle_heredoc_count(int type, int *heredoc_count)
{
	if (type == HEREDOC)
	{
		(*heredoc_count)++;
		if (*heredoc_count > 16)
		{
			return (write(2,
					"minishell: maximum here-document count exceeded\n",
					48));
		}
	}
	return (0);
}

int	check_syntax(t_token *tokens)
{
	int	last_type;
	int	heredoc_count;
	int	err;

	last_type = -1;
	heredoc_count = 0;
	while (tokens)
	{
		err = is_invalid_pipe_position(tokens, last_type);
		if (err)
			return (err);
		err = is_invalid_redirection(tokens);
		if (err)
			return (err);
		err = handle_heredoc_count(tokens->type, &heredoc_count);
		if (err)
			return (err);
		last_type = tokens->type;
		tokens = tokens->next;
	}
	return (0);
}
