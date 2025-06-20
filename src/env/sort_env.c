/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghou <iel-ghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:22:35 by iel-ghou          #+#    #+#             */
/*   Updated: 2025/06/20 11:26:35 by iel-ghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/execution.h"

int			str_env_len(char **env)
{
	int		i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void		sort_env(char **tab, int env_len)
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

// void		print_sorted_env(t_env *env)
// {
// 	int		i;
// 	char	**tab;
// 	char	*str_env;
// 	int oldpwd_found = 0;

// 	str_env = env_to_str(env);
// 	tab = ft_split(str_env, '\n');
// 	//ft_memdel(str_env);
// 	sort_env(tab, str_env_len(tab));
// 	i = 0;
// 	while (tab[i])
// 	{
// 		if (ft_strncmp(tab[i], "OLDPWD=", 7) == 0)
//             oldpwd_found = 1;
// 		ft_putstr("declare -x ");
// 		ft_putendl(tab[i]);
// 		i++;
// 	}
// 	if (!oldpwd_found)
//         ft_putendl("declare -x OLDPWD");
// 	//free_tab(tab);
// }
int env_len(t_env *env)
{
	int count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return count;
}

void print_sorted_env(t_env *env)
{
    int i = 0;
    char **tab;
    int len = env_len(env);  // count number of vars
    t_env *tmp = env;
    
    // Make a copy of all env->value strings
    tab = malloc(sizeof(char *) * (len + 1));
    if (!tab)
        return;
    
    while (tmp)
    {
        tab[i++] = ft_strdup(tmp->value);  // full "VAR=VAL" or just "VAR"
        tmp = tmp->next;
    }
    tab[i] = NULL;
    sort_env(tab, i);  // your sorting function

    i = 0;
    while (tab[i])
    {
        if (ft_strchr(tab[i], '='))
            printf("declare -x %s\n", tab[i]);
        else
            printf("declare -x %s\n", tab[i]);  // still print it
        //free(tab[i]);
        i++;
    }
    free(tab);
}
