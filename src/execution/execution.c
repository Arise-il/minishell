/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghou <iel-ghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 09:07:43 by iel-ghou          #+#    #+#             */
/*   Updated: 2025/06/25 16:31:04 by iel-ghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

static char	**env_to_array(t_env *env)
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

static void	execute_external(t_cmd *cmd, t_env *env)
{
	char		**envp;
	struct stat	st;
	int			err;

	envp = env_to_array(env);
	if (strchr(cmd->args[0], '/')
		&& stat(cmd->args[0], &st) == 0
		&& S_ISDIR(st.st_mode))
	{
		fprintf(stderr, "%s: Is a directory\n", cmd->args[0]);
		ft_malloc(0, 0);
		exit(126);
	}
	if (strchr(cmd->args[0], '/'))
	{
		if (access(cmd->args[0], F_OK) == 0)
		{
			if (access(cmd->args[0], X_OK) == 0)
				execve(cmd->args[0], cmd->args, envp);
			else
			{
				perror(cmd->args[0]);
				ft_malloc(0, 0);
				exit(126);
			}
		}
		else
		{
			fprintf(stderr, "%s: No such file or directory\n", cmd->args[0]);
			ft_malloc(0, 0);
			exit(127);
		}
	}
	else
		execvp(cmd->args[0], cmd->args);
	err = errno;
	if (err == ENOENT)
		fprintf(stderr, "%s: command not found\n", cmd->args[0]);
	else if (err == EACCES)
		fprintf(stderr, "%s: Permission denied\n", cmd->args[0]);
	else
		perror("minishell");
	ft_malloc(0, 0);
	if (err == EACCES)
		exit(126);
	else
		exit(127);
}

void	execute_commands(t_cmd *cmd_list, t_mini *mini)
{
	t_cmd	*cmd;
	int		pipe_fd[2];
	int		prev_read_fd;
	int		cmd_count;
	pid_t	*pids;
	int		i;
	int		status;
	t_cmd	*tmp;
	int		j;

	cmd = cmd_list;
	prev_read_fd = -1;
	cmd_count = 0;
	pids = NULL;
	i = 0;
	status = 0;
	tmp = cmd_list;
	j = 0;
	while (tmp)
	{
		cmd_count++;
		tmp = tmp->next;
	}
	pids = ft_malloc(sizeof(pid_t) * cmd_count, 1);
	if (!pids)
		return ;
	while (j < cmd_count)
	{
		pids[j] = -1;
		j++;
	}
	cmd = cmd_list;
	while (cmd)
	{
		if (!cmd->args || !cmd->args[0])
		{
			cmd = cmd->next;
			continue ;
		}
		if (cmd->pipe_after && pipe(pipe_fd) == -1)
		{
			perror("pipe");
			return ;
		}
		if (is_builtin(cmd->args[0])
			&& !cmd->pipe_after
			&& prev_read_fd == -1
			&& !cmd->infile)
			mini->exit_status = run_builtin_no_pipe(cmd, mini);
		else
		{
			pids[i] = fork();
			if (pids[i] == -1)
			{
				perror("fork");
				return ;
			}
			if (pids[i] == 0)
			{
				setup_pipes(cmd, prev_read_fd, pipe_fd);
				if (apply_redirections(cmd) == -1)
					exit(1);
				if (is_builtin(cmd->args[0]))
					exit(exec_builtin(cmd->args, mini));
				else
					execute_external(cmd, mini->env);
				exit(0);
			}
		}
		if (prev_read_fd != -1)
			close(prev_read_fd);
		if (cmd->pipe_after)
		{
			close(pipe_fd[1]);
			prev_read_fd = pipe_fd[0];
		}
		else
			prev_read_fd = -1;
		cmd = cmd->next;
		i++;
	}
	j = 0;
	while (j < i)
	{
		if (pids[j] > 0)
		{
			if (waitpid(pids[j], &status, 0) != -1)
			{
				if (WIFEXITED(status))
					mini->exit_status = WEXITSTATUS(status);
				else
					mini->exit_status = 1;
			}
		}
		j++;
	}
}

void	setup_pipes(t_cmd *cmd, int prev_read_fd, int pipe_fd[2])
{
	if (prev_read_fd != -1)
	{
		dup2(prev_read_fd, STDIN_FILENO);
		close(prev_read_fd);
	}
	if (cmd->pipe_after)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
}

void	close_unused_fds(int *prev_read_fd, t_cmd *cmd, int pipe_fd[2])
{
	if (*prev_read_fd != -1)
	{
		close(*prev_read_fd);
		*prev_read_fd = -1;
	}
	if (cmd->pipe_after)
	{
		close(pipe_fd[1]);
		*prev_read_fd = pipe_fd[0];
	}
}

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

int	apply_redirections(t_cmd *cmd)
{
	int	fd;

	if (cmd->redirection_error == 1)
	{
		if (cmd->infile)
			perror(cmd->infile);
		else
			perror(cmd->outfile);
		return (-1);
	}
	if (cmd->infile)
	{
		fd = open(cmd->infile, O_RDONLY);
		if (fd == -1)
		{
			perror(cmd->infile);
			return (-1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (cmd->outfile)
	{
		if (cmd->append)
			fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (perror(cmd->outfile), -1);
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (perror("dup2 outfile"), close(fd), -1);
		close(fd);
	}
	return (0);
}
