/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghou <iel-ghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 08:48:23 by iel-ghou          #+#    #+#             */
/*   Updated: 2025/06/25 16:30:37 by iel-ghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

int	is_builtin(char *command)
{
	if (ft_strcmp(command, "echo") == 0)
		return (1);
	if (ft_strcmp(command, "cd") == 0)
		return (1);
	if (ft_strcmp(command, "pwd") == 0)
		return (1);
	if (ft_strcmp(command, "env") == 0)
		return (1);
	if (ft_strcmp(command, "export") == 0)
		return (1);
	if (ft_strcmp(command, "unset") == 0)
		return (1);
	if (ft_strcmp(command, "exit") == 0)
		return (1);
	return (0);
}

int	exec_builtin(char **args, t_mini *mini)
{
	int		result;

	if (!args || !args[0])
		return (1);
	result = 0;
	if (ft_strcmp(args[0], "echo") == 0)
		result = ft_echo(args);
	else if (ft_strcmp(args[0], "cd") == 0)
		result = ft_cd(args, mini->env);
	else if (ft_strcmp(args[0], "pwd") == 0)
		result = ft_pwd(mini->env);
	else if (ft_strcmp(args[0], "env") == 0)
		result = ft_env(mini->env);
	else if (ft_strcmp(args[0], "export") == 0)
		result = ft_export(args, mini->env);
	else if (ft_strcmp(args[0], "unset") == 0)
		result = ft_unset(args, mini);
	else if (ft_strcmp(args[0], "exit") == 0)
		mini_exit(mini->cmds, args, mini);
	return (result);
}
