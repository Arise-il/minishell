/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_no_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghou <iel-ghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 18:14:10 by iel-ghou          #+#    #+#             */
/*   Updated: 2025/06/26 18:42:56 by iel-ghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

int	run_builtin_no_pipe(t_cmd *cmd, t_mini *mini)
{
	int	saved_stdin;
	int	saved_stdout;
	int	ret;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	ret = 0;
	if (strcmp(cmd->args[0], "exit") == 0)
	{
		mini_exit(cmd, cmd->args, mini);
		return (mini->exit_status);
	}
	if (apply_redirections(cmd) != -1)
		ret = exec_builtin(cmd->args, mini);
	else
		ret = 1;
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	mini->exit_status = ret;
	return (ret);
}
