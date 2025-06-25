/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghou <iel-ghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:22:35 by iel-ghou          #+#    #+#             */
/*   Updated: 2025/06/25 16:46:53 by iel-ghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

int	str_env_len(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	sort_env(char **tab, int env_len)
{
	int		ordered;
	int		i;
	char	*tmp;

	ordered = 0;
	while (tab && ordered == 0)
	{
		ordered = 1;
		i = 0;
		while (i < env_len - 1)
		{
			if (ft_strcmp(tab[i], tab[i + 1]) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = tmp;
				ordered = 0;
			}
			i++;
		}
		env_len--;
	}
}

int	env_len(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

void	print_sorted_env(t_env *env)
{
	int		i;
	char	**tab;
	int		len;
	t_env	*tmp;

	i = 0;
	len = env_len(env);
	tmp = env;
	tab = malloc(sizeof(char *) * (len + 1));
	if (!tab)
		return ;
	while (tmp)
	{
		tab[i++] = ft_strdup(tmp->value);
		tmp = tmp->next;
	}
	tab[i] = NULL;
	sort_env(tab, i);
	i = 0;
	while (tab[i])
	{
		if (ft_strchr(tab[i], '='))
			printf("declare -x %s\n", tab[i]);
		else
			printf("declare -x %s\n", tab[i]);
		i++;
	}
	free(tab);
}
