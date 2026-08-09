/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghou <iel-ghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 18:35:38 by iel-ghou          #+#    #+#             */
/*   Updated: 2025/07/02 15:52:13 by iel-ghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

char	**env_to_array(t_env *env)
{
	int		i;
	t_env	*tmp;
	char	**arr;

	i = 0;
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	arr = ft_malloc(sizeof(char *) * (i + 1), 1);
	if (!arr)
		return (NULL);
	i = 0;
	while (env)
	{
		arr[i++] = ft_strdup(env->value);
		env = env->next;
	}
	arr[i] = NULL;
	return (arr);
}

void	wait_for_children(pid_t *pids, int total, t_mini *mini)
{
	int	status;
	int	i;

	i = 0;
	while (i < total)
	{
		if (pids[i] > 0 && waitpid(pids[i], &status, 0) != -1)
		{
			if (WIFEXITED(status))
				mini->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				mini->exit_status = 128 + WTERMSIG(status);
			else if (WIFSTOPPED(status))
				mini->exit_status = 128 + WSTOPSIG(status);
			else
				mini->exit_status = 1;
			if (WTERMSIG(status) == SIGQUIT || WTERMSIG(status) == SIGINT)
				write(1, "\n", 1);
		}
		i++;
	}
}

int	update_fds(int prev_read_fd, t_cmd *cmd, int pipe_fd[2])
{
	if (prev_read_fd != -1)
		close(prev_read_fd);
	if (cmd->pipe_after)
	{
		close(pipe_fd[1]);
		return (pipe_fd[0]);
	}
	return (-1);
}

int	count_commands(t_cmd *cmd_list)
{
	int		count;

	count = 0;
	while (cmd_list)
	{
		count++;
		cmd_list = cmd_list->next;
	}
	return (count);
}

int	prepare_command(t_cmd *cmd, int pipe_fd[2])
{
	if (cmd->pipe_after && pipe(pipe_fd) == -1)
		return (perror("pipe"), -1);
	return (0);
}
