/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghou <iel-ghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 08:35:47 by iel-ghou          #+#    #+#             */
/*   Updated: 2025/06/25 17:16:14 by iel-ghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

void	mini_exit(t_cmd *cmd, char **args, t_mini *mini)
{
	long	exit_code;

	(void)cmd;
	if (isatty(STDIN_FILENO))
		ft_putendl_fd("exit", STDOUT);
	if (args[1] && args[2] && ft_strisnum(args[1]))
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR);
		if (cmd)
			mini->exit_status = 1;
		return ;
	}
	else if (args[1]
		&& (!ft_strisnum(args[1])
			|| ft_atol(args[1]) > LLONG_MAX_STR))
	{
		ft_putstr_fd("minishell: exit: ", STDERR);
		ft_putstr_fd(args[1], STDERR);
		ft_putendl_fd(": numeric argument required", STDERR);
		ft_malloc(0, 0);
		exit(2);
	}
	if (args[1])
	{
		exit_code = (unsigned char)ft_atol(args[1]);
		ft_malloc(0, 0);
		exit(exit_code);
	}
	ft_malloc(0, 0);
	exit(0);
}
