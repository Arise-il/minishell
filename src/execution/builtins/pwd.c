/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghou <iel-ghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 08:35:19 by iel-ghou          #+#    #+#             */
/*   Updated: 2025/07/02 17:04:29 by iel-ghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

int	ft_pwd(t_env *env)
{
	char	*cwd;
	char	*new_pwd;
	char	*pwd_env;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		ft_putendl_fd(cwd, 1);
		new_pwd = ft_strjoin("PWD=", cwd);
		if (!new_pwd)
			return (free(cwd), ERROR);
		env_add(new_pwd, env);
		free(cwd);
		return (SUCCESS);
	}
	else
	{
		ft_putendl_fd("minishell: pwd: error retrieving current directory", 2);
		pwd_env = get_env_value("PWD", env);
		if (pwd_env && pwd_env[0] != '\0')
			ft_putendl_fd(pwd_env, 1);
		return (ERROR);
	}
}
