/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghou <iel-ghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:36:42 by iel-ghou          #+#    #+#             */
/*   Updated: 2025/06/26 13:35:01 by iel-ghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

char	*ft_strjoin1(const char *s1, const char *s2)
{
	char	*concat;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	concat = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (concat == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		concat[j++] = s1[i++];
	}
	i = 0;
	while (s2[i])
	{
		concat[j++] = s2[i++];
	}
	concat[j] = '\0';
	return (concat);
}

void	cd_success(t_env *env, char *oldpwd)
{
	char	*new_pwd;
	char	*oldpwd_str;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		ft_putstr_fd(
			"minishell: pwd: error retrieving current directory: "
			"No such file or directory\n", 2);
		return ;
	}
	free(new_pwd);
	if (oldpwd)
	{
		oldpwd_str = ft_strjoin("OLDPWD=", oldpwd);
		if (env_update(oldpwd_str, env) == ERROR)
			env_add(oldpwd_str, env);
	}
	update_pwd(env);
}

int	update_pwd(t_env *env)
{
	char	cwd[4096];
	char	*pwd;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (ERROR);
	pwd = ft_strjoin("PWD=", cwd);
	if (!pwd)
		return (ERROR);
	while (env)
	{
		if (ft_strncmp(env->value, "PWD=", 4) == 0)
		{
			env->value = pwd;
			return (SUCCESS);
		}
		env = env->next;
	}
	env_add(pwd, env);
	return (SUCCESS);
}
