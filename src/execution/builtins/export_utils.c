/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghou <iel-ghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:36:01 by iel-ghou          #+#    #+#             */
/*   Updated: 2025/06/26 13:39:31 by iel-ghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

int	is_valid_identifier(const char *s)
{
	int	i;

	i = 0;
	if (!s || !s[0])
		return (0);
	if (!(ft_isalpha(s[0]) || s[0] == '_'))
		return (0);
	while (s[i] && s[i] != '=')
	{
		if (!(ft_isalnum(s[i]) || s[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

int	is_in_env(t_env *env, char *args)
{
	char	var_name[BUFF_SIZE];
	char	env_name[BUFF_SIZE];

	get_env_name(var_name, args);
	while (env)
	{
		get_env_name(env_name, env->value);
		if (ft_strcmp(var_name, env_name) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

int	env_update(char *new_value, t_env *env)
{
	char	var_name[BUFF_SIZE];
	char	env_name[BUFF_SIZE];

	get_env_name(var_name, new_value);
	while (env)
	{
		get_env_name(env_name, env->value);
		if (ft_strcmp(var_name, env_name) == 0)
		{
			env->value = ft_strdup(new_value);
			if (!env->value)
				return (ERROR);
			return (SUCCESS);
		}
		env = env->next;
	}
	return (ERROR);
}
