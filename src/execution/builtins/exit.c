/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghou <iel-ghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:33:17 by iel-ghou          #+#    #+#             */
/*   Updated: 2025/06/26 13:29:25 by iel-ghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

void	handle_too_many_args(t_cmd *cmd, t_mini *mini)
{
	ft_putendl_fd("minishell: exit: too many arguments", STDERR);
	if (cmd)
		mini->exit_status = 1;
}

void	handle_invalid_arg(char *arg)
{
	ft_putstr_fd("minishell: exit: ", STDERR);
	ft_putstr_fd(arg, STDERR);
	ft_putendl_fd(": numeric argument required", STDERR);
	ft_malloc(0, 0);
	exit(2);
}

long long	ft_atol_with_overflow(const char *str, int *overflow)
{
	int			i;
	int			sign;
	long long	num;

	num = 0;
	sign = 1;
	i = 0;
	*overflow = 0;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (num > (LLONG_MAX - (str[i] - '0')) / 10)
		{
			*overflow = 1;
			if (sign == 1)
				return (LLONG_MAX);
			else
				return (LLONG_MIN);
		}
		num = num * 10 + (str[i++] - '0');
	}
	return (num * sign);
}

void	mini_exit(t_cmd *cmd, char **args, t_mini *mini)
{
	long		exit_code;
	int			overflow;
	long long	val;

	val = ft_atol_with_overflow(args[1], &overflow);
	(void)val;
	(void)cmd;
	if (isatty(STDIN_FILENO))
		ft_putendl_fd("exit", STDOUT);
	if (args[1] && args[2] && ft_strisnum(args[1]))
	{
		handle_too_many_args(cmd, mini);
		return ;
	}
	else if (!ft_strisnum(args[1]) || overflow)
		handle_invalid_arg(args[1]);
	if (args[1])
	{
		exit_code = (unsigned char)ft_atol(args[1]);
		ft_malloc(0, 0);
		exit(exit_code);
	}
	ft_malloc(0, 0);
	exit(0);
}
