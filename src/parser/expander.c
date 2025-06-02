/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouhlale <oouhlale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:29:46 by oouhlale          #+#    #+#             */
/*   Updated: 2025/06/02 14:31:15 by oouhlale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Expand one token into a full expanded string (with quotes respected)
char	*expand_token_string(const char *str, t_env *env, int last_status)
{
	int				i = 0;
	int				in_single = 0;
	int				in_double = 0;
	char			*result = ft_calloc(1, 1);
	t_expand_data	data;

	data.str = str;
	data.i = &i;
	data.env = env;
	data.last_status = last_status;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (str[i] == '\"' && !in_single)
			in_double = !in_double;
		else if (str[i] == '$' && !in_single)
		{
			if (str[i + 1] == '\0' || (!ft_isalpha(str[i + 1]) && str[i + 1] != '_' && str[i + 1] != '?'))
				result = append_char(result, str, i);
			else
			{
				result = append_var(data, result);
				continue ;
			}
		}
		else
			result = append_char(result, str, i);
		i++;
	}
	return (result);
}

// Replace original token with potentially multiple new tokens after expansion
void	expand_tokens(t_token **tokens, t_env *env, int last_status)
{
	t_token	*cur;
	t_token	*new;
	char	*expanded;
	char	**parts;
	int		j;

	cur = *tokens;
	while (cur)
	{
		if (cur->type == WORD)
		{
			expanded = expand_token_string(cur->value, env, last_status);
			if (cur->quoted)
				cur->value = expanded;
			else
			{
				if (!expanded)
					expanded = ft_strdup("");
				parts = ft_split(expanded, ' ');
				//printf("--%s--", parts[1]);
				if (parts[0])
					cur->value = ft_strdup(parts[0]);
				else
					cur->value = ft_strdup("");
				j = 1;
				// printf("%p\n",parts[j]);
				while (parts && parts[j])
				{
					new = new_token(ft_strdup(parts[j]), WORD, 0);
					new->next = cur->next;
					cur->next = new;
					cur = new;
					j++;
				}
			}
		}
		cur = cur->next;
	}
}
