/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghou <iel-ghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 08:35:27 by iel-ghou          #+#    #+#             */
/*   Updated: 2025/06/20 11:07:14 by iel-ghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../../includes/execution.h"

static void		print_error(char **args)
{
	ft_putstr_fd("cd: ", 2);
	if (args[2]) // If a third argument exists (args[2]), it prints too many arguments
		ft_putstr_fd("too many arguments\n", 2);
	else
	{
		// ft_putendl_fd(args[1], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);//It prints a description of the most recent error (based on errno) to the standard error.
		ft_putstr_fd("\n", 2);
	}
}

static char		*get_env_path(t_env *env, const char *var, size_t len)
{
	char	*oldpwd;
	int		s_alloc;

	while (env) // original : while (env && env->next != NULL) // This loops over the linked list
	{
		if (ft_strncmp(env->value, var, len) == 0 && env->value[len] == '=') // Check if prefix matches AND the next char is '='
		{
			s_alloc = ft_strlen(env->value) - (len + 1);
			oldpwd = ft_malloc(sizeof(char) * (s_alloc + 1), 1);
            if (!oldpwd)
                return NULL;
			ft_strcpy(oldpwd, env->value + len + 1); // Copy value part after 'var='
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
			//free(env->value);
			env->value = oldpwd;  // Take ownership of oldpwd
			return (SUCCESS);
		}
		env = env->next;
	}

	// Not found, add to env
	env_add(oldpwd, env);
	//free(oldpwd); // env_add makes a copy
	return (SUCCESS);
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
			//free(env->value);
			env->value = pwd;  // Take ownership
			return (SUCCESS);
		}
		env = env->next;
	}

	// Not found, add to env
	env_add(pwd, env);
	//free(pwd); // env_add makes a copy
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
		update_oldpwd(env);  // Only update if chdir succeeded
	//ft_memdel(env_path);
	return (ret);
}

int				ft_cd(char **args, t_env *env)
{
	int		cd_ret;
	char 	*oldpwd;
	

	if (!args[1]) //If no arguments: go to HOME
		return (go_to_path(0, env));
	if (args[2])
	{
		print_error(args);
		return (1); // Return 1 for error if only one argument is given
	}
		
	if (ft_strcmp(args[1], "-") == 0) //If argument is -: go to OLDPWD
		cd_ret = go_to_path(1, env);
	oldpwd = get_env_value("PWD", env);
	if (!oldpwd)
    	oldpwd = getcwd(NULL, 0);
    cd_ret = chdir(args[1]);
	if (cd_ret == 0)
    {
        // On success, update OLDPWD and PWD
        if (oldpwd)
        {
            char *oldpwd_str = ft_strjoin("OLDPWD=", oldpwd);
            if (env_update(oldpwd_str, env) == ERROR)
    			env_add(oldpwd_str, env);
            free(oldpwd_str);
        }
        update_pwd(env); // This should get current directory and update PWD in env
    }
    else
    {
        print_error(args);
    }
	if (cd_ret < 0)
		return (-cd_ret);
	return (cd_ret);
}

