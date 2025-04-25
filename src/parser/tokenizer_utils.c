/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouhlale <oouhlale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:52:05 by oouhlale          #+#    #+#             */
/*   Updated: 2025/04/25 08:58:19 by oouhlale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*new_token(char *value, t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = type;
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

char	*extract_quoted(char *str, int *i)
{
	char	quote;
	int		start;
	char	*val;

	quote = str[(*i)++];
	start = *i;
	while (str[*i] && str[*i] != quote)
		(*i)++;
	val = ft_substr(str, start, *i - start);
	if (str[*i] == quote)
		(*i)++;
	return (val);
}

char	*extract_word(char *str, int *i)
{
	int	start;

	start = *i;
	while (str[*i] && str[*i] != ' ' && str[*i] != '\t'
		&& !is_operator(str[*i]))
		(*i)++;
	return (ft_substr(str, start, *i - start));
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
		op = malloc(2);
		if (!op)
			return (NULL);
		op[0] = line[*i];
		op[1] = '\0';
		(*i)++;
		return (op);
	}
	return (NULL);
}
