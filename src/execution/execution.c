/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghou <iel-ghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 09:07:43 by iel-ghou          #+#    #+#             */
/*   Updated: 2025/07/02 17:04:55 by iel-ghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

pid_t	fork_and_execute(
	t_cmd *cmd,
	int prev_read_fd,
	int pipe_fd[2],
	t_mini *mini
)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		setup_pipes(cmd, prev_read_fd, pipe_fd);
		if (apply_redirections(cmd) == -1)
			exit(1);
		if (!cmd->args || !cmd->args[0])
			exit (0);
		if (is_builtin(cmd->args[0]))
			exit(exec_builtin(cmd->args, mini));
		execute_external(cmd, mini->env);
		exit(0);
	}
	return (pid);
}

pid_t	*init_pids(int count)
{
	pid_t	*pids;
	int		i;

	pids = ft_malloc(sizeof(pid_t) * count, 1);
	i = 0;
	if (!pids)
		return (NULL);
	while (i < count)
		pids[i++] = -1;
	return (pids);
}

pid_t	execute_command_logic(
	t_cmd *cmd,
	int prev_read_fd,
	int pipe_fd[2],
	t_mini *mini
)
{
	if (cmd && cmd->args && is_builtin(cmd->args[0])
		&& !cmd->pipe_after
		&& prev_read_fd == -1
		&& !cmd->infile)
	{
		mini->exit_status = run_builtin_no_pipe(cmd, mini);
		return (-2);
	}
	return (fork_and_execute(cmd, prev_read_fd, pipe_fd, mini));
}

int	execute_single_command(
	int *prev_read_fd,
	pid_t *pids,
	int *index,
	t_mini *mini
)
{
	int		pipe_fd[2];
	int		ret;
	pid_t	pid;

	ret = prepare_command(mini->current_cmd, pipe_fd);
	if (ret == -1)
		return (-1);
	if (ret == 0)
	{
		pid = execute_command_logic(
				mini->current_cmd,
				*prev_read_fd,
				pipe_fd,
				mini);
		if (pid == -1)
			return (-1);
		pids[*index] = pid;
		if (pid != -2)
			(*index)++;
	}
	*prev_read_fd = update_fds(*prev_read_fd, mini->current_cmd, pipe_fd);
	return (0);
}

void	execute_commands(t_cmd *cmd_list, t_mini *mini)
{
	int		cmd_count;
	pid_t	*pids;
	int		prev_read_fd;
	int		i;

	cmd_count = count_commands(cmd_list);
	pids = init_pids(cmd_count);
	if (!pids)
		return ;
	prev_read_fd = -1;
	i = 0;
	mini->current_cmd = cmd_list;
	while (mini->current_cmd)
	{
		if (execute_single_command(&prev_read_fd, pids, &i, mini) == -1)
			return ;
		mini->current_cmd = mini->current_cmd->next;
	}
	wait_for_children(pids, i, mini);
}
