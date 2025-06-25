/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghou <iel-ghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 08:35:19 by iel-ghou          #+#    #+#             */
/*   Updated: 2025/06/25 16:32:19 by iel-ghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

int	ft_pwd(t_env *env)
{
	char	*pwd_env;
	char	*cwd;

	pwd_env = get_env_value("PWD", env);
	if (pwd_env)
	{
		ft_putendl_fd(pwd_env, 1);
		return (SUCCESS);
	}
	else
	{
		cwd = getcwd(NULL, 0);
		if (!cwd)
		{
			ft_putendl_fd("minishell: pwd: ", 2);
			ft_putendl_fd("error retrieving current directory", 2);
			return (ERROR);
		}
		ft_putendl_fd(cwd, 1);
		return (SUCCESS);
	}
}
