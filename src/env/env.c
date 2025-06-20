/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghou <iel-ghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 08:36:09 by iel-ghou          #+#    #+#             */
/*   Updated: 2025/06/20 10:55:23 by iel-ghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/execution.h"

size_t			size_env(t_env *lst)
{
	size_t	lst_len;

	lst_len = 0;
	while (lst && lst->next != NULL)
	{
		if (lst->value != NULL)
		{
			lst_len += ft_strlen(lst->value);
			lst_len++;
		}
		lst = lst->next;
	}
	return (lst_len);
}

char			*env_to_str(t_env *lst)
{
	char	*env;
	int		i;
	int		j;

	if (!(env = ft_malloc(sizeof(char) * size_env(lst) + 1, 1)))
		return (NULL);
	i = 0;
	while (lst && lst->next != NULL)
	{
		if (lst->value != NULL)
		{
			j = 0;
			while (lst->value[j])
			{
				env[i] = lst->value[j];
				i++;
				j++;
			}
		}
		if (lst->next->next != NULL)
			env[i++] = '\n';
		lst = lst->next;
	}
	env[i] = '\0';
	return (env);
}
void add_env(t_env **env_list, char *value)
{
    t_env *new_node;
    t_env *tmp;

    new_node = ft_malloc(sizeof(t_env), 1);
    if (!new_node)
        return; // handle malloc failure as you want

    new_node->value = value;  // take ownership of the string pointer
    new_node->next = NULL;

    if (!*env_list)
    {
        *env_list = new_node;
        return;
    }

    tmp = *env_list;
    while (tmp->next)
        tmp = tmp->next;

    tmp->next = new_node;
}

int				env_init(t_mini *mini, char **env_array)
{
	t_env	*env;
	t_env	*new;
	int		i;

	mini->env = NULL;  // start empty
	if (!env_array || !*env_array)
	{
		char cwd[1024];
		if (getcwd(cwd, sizeof(cwd)))
		{
			add_env(&mini->env, ft_strjoin("PWD=", cwd));
			add_env(&mini->env, ft_strdup("SHLVL=1"));
			add_env(&mini->env, ft_strdup("_=/usr/bin/env"));
		}
		return (0); // ✅ early return to prevent crash
	}

	// ✅ Continue if env_array is not empty
	env = ft_malloc(sizeof(t_env), 1);
	if (!env)
		return (1);
	env->value = ft_strdup(env_array[0]);
	env->next = NULL;
	mini->env = env;
	i = 1;
	while (env_array && env_array[0] && env_array[i])
	{
		if (!(new = ft_malloc(sizeof(t_env), 1)))
			return (1);
		new->value = ft_strdup(env_array[i]);
		new->next = NULL;
		env->next = new;
		env = new;
		i++;
	}
	return (0);
}

int				secret_env_init(t_mini *mini, char **env_array)
{
	t_env	*env;
	t_env	*new;
	int		i;

	if (!(env = ft_malloc(sizeof(t_env), 1)))
		return (1);
	env->value = ft_strdup(env_array[0]);
	env->next = NULL;
	mini->secret_env = env;
	i = 1;
	while (env_array && env_array[0] && env_array[i])
	{
		if (!(new = ft_malloc(sizeof(t_env), 1)))
			return (1);
		new->value = ft_strdup(env_array[i]);
		new->next = NULL;
		env->next = new;
		env = new;
		i++;
	}
	return (0);
}
