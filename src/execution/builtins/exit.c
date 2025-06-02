/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouhlale <oouhlale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 08:35:47 by iel-ghou          #+#    #+#             */
/*   Updated: 2025/06/01 17:15:48 by oouhlale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../../includes/execution.h"



// void	mini_exit(t_mini *mini, char **cmd)
// {
// 	mini->exit = 1;
// 	ft_putstr_fd("exit ", STDERR);
// 	// cmd[1] ? ft_putendl_fd("❤️", STDERR) : ft_putendl_fd("💚", STDERR);//Prints exit ❤️ if an argument is given, or exit 💚 if not. Cute, but might be unconventional for users of a shell.
// 	if (cmd[1] && cmd[2])//If more than one argument is given, prints an error and sets return code to 1
// 	{
// 		mini->ret = 1;
// 		ft_putendl_fd("minishell: exit: too many arguments", STDERR);
// 	}
// 	else if (cmd[1] && ft_strisnum(cmd[1]) == 0)//If the first argument is not numeric, sets return code to 255 and shows an error.
// 	{
// 		mini->ret = 255;
// 		ft_putstr_fd("minishell: exit: ", STDERR);
// 		ft_putstr_fd(cmd[1], STDERR);
// 		ft_putendl_fd(": numeric argument required", STDERR);
// 	}
// 	else if (cmd[1]) //if the argument is numeric, converts it to int and sets as return code.
// 		mini->ret = (unsigned char)ft_atoi(cmd[1]);
// 	else
// 		mini->ret = 0;
// }







//here is mini_exit function with immediate exit and Bash-like behavior
//test it if the first one does not work
//
// #include <stdlib.h> //Required for the exit() function.

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
		return;
	}
	else if (args[1] && !ft_strisnum(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR);
		ft_putstr_fd(args[1], STDERR);
		ft_putendl_fd(": numeric argument required", STDERR);
		ft_malloc(0, 0); // Free all allocated memory
		exit(2);
	}
	if (args[1]) // Valid numeric
	{
		exit_code = (unsigned char)ft_atol(args[1]); // ✅ Compute before freeing
		ft_malloc(0, 0); // ✅ Now free
		exit(exit_code); // ✅ Use value after free
	}

	ft_malloc(0, 0);
	exit(0);
}
