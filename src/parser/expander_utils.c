/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouhlale <oouhlale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 08:27:01 by oouhlale          #+#    #+#             */
/*   Updated: 2025/07/03 15:17:34 by oouhlale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*extract_var_name(const char *str, int *i)
{
	int	start;

	start = *i;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_strdup("?"));
	}
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

char	*get_var_value(const char *name, t_env *env, int last_status)
{
	size_t	name_len;

	if (ft_strcmp(name, "?") == 0)
		return (ft_itoa(last_status));
	name_len = ft_strlen(name);
	while (env)
	{
		if (ft_strncmp(env->value, name, name_len) == 0
			&& env->value[name_len] == '=')
			return (ft_strdup(env->value + name_len + 1));
		env = env->next;
	}
	return (ft_strdup(""));
}

char	*append_char(char *result, const char *str, int i)
{
	char	*ch;
	char	*tmp;

	ch = ft_substr(str, i, 1);
	tmp = ft_strjoin(result, ch);
	return (tmp);
}

char	*append_var(t_expand_data data, char *result)
{
	char	*var_name;
	char	*value;
	char	*tmp;

	(*data.i)++;
	var_name = extract_var_name(data.str, data.i);
	value = get_var_value(var_name, data.env, data.last_status);
	tmp = ft_strjoin(result, value);
	return (tmp);
}
