/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouhlale <oouhlale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:51:02 by oouhlale          #+#    #+#             */
/*   Updated: 2025/04/28 09:47:27 by oouhlale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token_type	get_token_type(char *value)
{
	if (!strcmp(value, "|"))
		return (PIPE);
	if (!strcmp(value, "<"))
		return (REDIR_IN);
	if (!strcmp(value, ">"))
		return (REDIR_OUT);
	if (!strcmp(value, "<<"))
		return (HEREDOC);
	if (!strcmp(value, ">>"))
		return (REDIR_APPEND);
	return (WORD);
}

t_token	*tokenize_input(char *line)
{
	t_token	*tokens;
	int		i;
	char	*quoted;
	char	*word;
	char	*op;

	tokens = NULL;
	i = 0;
	while (line[i])
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (is_quote(line[i]))
		{
			quoted = extract_quoted(line, &i);
			add_token(&tokens, new_token(quoted, WORD));
		}
		else if (is_operator(line[i]))
		{
			op = extract_operator(line, &i);
			add_token(&tokens, new_token(op, get_token_type(op)));
		}
		else if (line[i])
		{
			word = extract_word(line, &i);
			add_token(&tokens, new_token(word, WORD));
		}
	}
	return (tokens);
}
