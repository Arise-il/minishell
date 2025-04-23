/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouhlale <oouhlale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:51:02 by oouhlale          #+#    #+#             */
/*   Updated: 2025/04/22 17:46:38 by oouhlale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*tokenize_input(char *line)
{
	t_token	*tokens;
	int		i;
	char	*quoted;
	char	*word;

	tokens = NULL;
	i = 0;
	while (line[i])
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] == '\'' || line[i] == '"')
		{
			quoted = extract_quoted(line, &i);
			add_token(&tokens, new_token(quoted));
		}
		else if (line[i])
		{
			word = extract_word(line, &i);
			add_token(&tokens, new_token(word));
		}
	}
	return (tokens);
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = tmp;
	}
}
