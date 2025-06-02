/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouhlale <oouhlale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:52:05 by oouhlale          #+#    #+#             */
/*   Updated: 2025/06/01 14:30:23 by oouhlale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*new_token(char *value, t_token_type type, int quoted)
{
	t_token	*token;

	token = ft_malloc(sizeof(t_token), 1);
	if (!token)
		return (NULL);
	token->value = value;
	token->type = type;
	token->quoted = quoted;
	token->next = NULL;
	return (token);
}

void	add_token(t_token **head, t_token *new)
{
	t_token	*tmp;

	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

char	*extract_word(char *line, int *i, int *was_quoted)
{
	int		start;
	int		quoted;
	char	quote;

	start = *i;
	quoted = 0;
	while (line[*i] && !ft_isspace(line[*i]) && !is_operator(line[*i]))
	{
		if (is_quote(line[*i]))
		{
			quoted = 1;
			quote = line[(*i)++];
			while (line[*i] && line[*i] != quote)
				(*i)++;
			if (line[*i] == quote)
				(*i)++;
		}
		else
			(*i)++;
	}
	if (was_quoted)
		*was_quoted = quoted;
	return (ft_substr(line, start, *i - start));
}

char	*extract_operator(const char *line, int *i)
{
	char	*op;

	if (line[*i] == '>' && line[*i + 1] == '>')
	{
		(*i) += 2;
		return (ft_strdup(">>"));
	}
	else if (line[*i] == '<' && line[*i + 1] == '<')
	{
		(*i) += 2;
		return (ft_strdup("<<"));
	}
	else if (line[*i] == '>' || line[*i] == '<' || line[*i] == '|')
	{
		op = ft_malloc(2, 1);
		if (!op)
			return (NULL);
		op[0] = line[*i];
		op[1] = '\0';
		(*i)++;
		return (op);
	}
	return (NULL);
}
