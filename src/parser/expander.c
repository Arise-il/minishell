/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouhlale <oouhlale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:29:46 by oouhlale          #+#    #+#             */
/*   Updated: 2025/07/03 15:17:50 by oouhlale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*expansion_logic(const char *str,
	t_expand_data *data, char *result)
{
	int	i;

	i = *(data->i);
	if (str[i] == '\'' && !data->in_double)
		data->in_single = !data->in_single;
	else if (str[i] == '\"' && !data->in_single)
		data->in_double = !data->in_double;
	else if (str[i] == '$' && !data->in_single)
	{
		if (str[i + 1] == '\0' || (!ft_isalpha(str[i + 1])
				&& str[i + 1] != '_' && str[i + 1] != '?'))
			result = append_char(result, str, i);
		else
		{
			result = append_var(*data, result);
			return (result);
		}
	}
	else
		result = append_char(result, str, i);
	(*data->i)++;
	return (result);
}

char	*expand_token_string(const char *str, t_env *env, int last_status)
{
	int				i;
	char			*result;
	t_expand_data	data;

	i = 0;
	result = ft_calloc(1, 1);
	data.str = str;
	data.in_single = 0;
	data.in_double = 0;
	data.i = &i;
	data.env = env;
	data.last_status = last_status;
	while (str[i])
		result = expansion_logic(str, &data, result);
	return (result);
}

static void	expand_unquoted_parts(t_token *cur, char *expanded)
{
	char	**parts;
	t_token	*new;
	int		j;

	if (!expanded)
		expanded = ft_strdup("");
	parts = ft_split(expanded, ' ');
	if (parts[0])
		cur->value = ft_strdup(parts[0]);
	else
		cur->value = NULL;
	if (parts && parts[0] == NULL)
		parts = NULL;
	j = 1;
	while (parts && parts[j])
	{
		new = new_token(ft_strdup(parts[j]), WORD, 0);
		new->next = cur->next;
		cur->next = new;
		cur = new;
		j++;
	}
}

void	expand_tokens(t_token **tokens, t_env *env, int last_status)
{
	t_token	*cur;
	char	*expanded;

	cur = *tokens;
	while (cur)
	{
		if (cur->type == WORD)
		{
			expanded = expand_token_string(cur->value, env, last_status);
			if (cur->quoted)
				cur->value = expanded;
			else
				expand_unquoted_parts(cur, expanded);
		}
		cur = cur->next;
	}
}
