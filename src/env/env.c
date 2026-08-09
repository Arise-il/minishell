/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghou <iel-ghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 08:36:09 by iel-ghou          #+#    #+#             */
/*   Updated: 2025/07/02 16:35:52 by iel-ghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

void	add_env(t_env **env_list, char *value)
{
	t_env	*new_node;
	t_env	*tmp;

	new_node = ft_malloc(sizeof(t_env), 1);
	if (!new_node)
		return ;
	new_node->value = value;
	new_node->next = NULL;
	if (!*env_list)
	{
		*env_list = new_node;
		return ;
	}
	tmp = *env_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

static int	init_default_env(t_env **env)
{
	char	cwd[1024];

	if (!getcwd(cwd, sizeof(cwd)))
		return (1);
	add_env(env, ft_strjoin("PWD=", cwd));
	add_env(env, ft_strdup("SHLVL=1"));
	add_env(env, ft_strdup("_=/usr/bin/env"));
	return (0);
}

static int	append_env_node(t_env **env, char *value)
{
	t_env	*new;

	new = ft_malloc(sizeof(t_env), 1);
	if (!new)
		return (1);
	new->value = ft_strdup(value);
	new->next = NULL;
	(*env)->next = new;
	*env = new;
	return (0);
}

int	env_init(t_mini *mini, char **env_array)
{
	t_env	*env;
	int		i;

	mini->env = NULL;
	if (!env_array || !*env_array)
		return (init_default_env(&mini->env));
	env = ft_malloc(sizeof(t_env), 1);
	if (!env)
		return (1);
	env->value = ft_strdup(env_array[0]);
	env->next = NULL;
	mini->env = env;
	i = 1;
	while (env_array[i])
	{
		if (append_env_node(&env, env_array[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}
