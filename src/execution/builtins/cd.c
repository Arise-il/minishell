/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghou <iel-ghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 08:35:27 by iel-ghou          #+#    #+#             */
/*   Updated: 2025/06/25 17:45:39 by iel-ghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

static void	print_error(char **args)
{
	ft_putstr_fd("cd: ", 2);
	if (args[2])
		ft_putstr_fd("too many arguments\n", 2);
	else
	{
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
}

static char	*get_env_path(t_env *env, const char *var, size_t len)
{
	char	*oldpwd;
	int		s_alloc;

	while (env)
	{
		if (ft_strncmp(env->value, var, len) == 0 && env->value[len] == '=')
		{
			s_alloc = ft_strlen(env->value) - (len + 1);
			oldpwd = ft_malloc(sizeof(char) * (s_alloc + 1), 1);
			if (!oldpwd)
				return (NULL);
			ft_strcpy(oldpwd, env->value + len + 1);
			return (oldpwd);
		}
		env = env->next;
	}
	return (NULL);
}

static int	update_oldpwd(t_env *env)
{
	char	cwd[4096];
	char	*oldpwd;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (ERROR);
	oldpwd = ft_strjoin("OLDPWD=", cwd);
	if (!oldpwd)
		return (ERROR);
	while (env)
	{
		if (ft_strncmp(env->value, "OLDPWD=", 7) == 0)
		{
			env->value = oldpwd;
			return (SUCCESS);
		}
		env = env->next;
	}
	env_add(oldpwd, env);
	return (SUCCESS);
}

static int	go_to_path(int option, t_env *env)
{
	int		ret;
	char	*env_path;

	env_path = NULL;
	if (option == 0)
		env_path = get_env_path(env, "HOME", 4);
	else if (option == 1)
		env_path = get_env_path(env, "OLDPWD", 6);
	if (!env_path)
	{
		if (option == 0)
			ft_putendl_fd("minishell: cd: HOME not set", STDERR);
		else
			ft_putendl_fd("minishell: cd: OLDPWD not set", STDERR);
		return (ERROR);
	}
	ret = chdir(env_path);
	if (ret == 0)
		update_oldpwd(env);
	return (ret);
}

int	ft_cd(char **args, t_env *env)
{
	int		cd_ret;
	char	*oldpwd;

	if (!args[1])
		return (go_to_path(0, env));
	if (args[2])
		return (print_error(args), 1);
	if (ft_strcmp(args[1], "-") == 0)
		return (go_to_path(1, env));
	oldpwd = get_env_value("PWD", env);
	if (!oldpwd)
		oldpwd = getcwd(NULL, 0);
	cd_ret = chdir(args[1]);
	if (cd_ret == 0)
		cd_success(env, oldpwd);
	else
		print_error(args);
	if (cd_ret < 0)
		return (-cd_ret);
	return (cd_ret);
}
