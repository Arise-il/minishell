/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouhlale <oouhlale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 09:07:43 by iel-ghou          #+#    #+#             */
/*   Updated: 2025/06/01 17:16:24 by oouhlale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

static char	**env_to_array(t_env *env)
{
	int		i = 0;
	t_env	*tmp = env;
	char	**arr;

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
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/stat.h>

static void execute_external(t_cmd *cmd, t_env *env)
{
    char **envp = env_to_array(env);
    struct stat st;

    // Check if command path contains '/' and is a directory
    if (strchr(cmd->args[0], '/') && stat(cmd->args[0], &st) == 0 && S_ISDIR(st.st_mode))
    {
        fprintf(stderr, "%s: Is a directory\n", cmd->args[0]);
        // free_split(envp);
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
                // free_split(envp);
				ft_malloc(0, 0);
                exit(126);
            }
        }
        else
        {
            fprintf(stderr, "%s: No such file or directory\n", cmd->args[0]);
            // free_split(envp);
			ft_malloc(0, 0);
            exit(127);
        }
    }
    else
    {
        execvp(cmd->args[0], cmd->args);
    }

    int err = errno;
    if (err == ENOENT)
        fprintf(stderr, "%s: command not found\n", cmd->args[0]);
    else if (err == EACCES)
        fprintf(stderr, "%s: Permission denied\n", cmd->args[0]);
    else
	{
        perror("minishell");
	}
    // free_split(envp);
	ft_malloc(0, 0);
    if (err == EACCES)
        exit(126);
    else
        exit(127);
}




void execute_commands(t_cmd *cmd_list, t_mini *mini)
{
	t_cmd *cmd = cmd_list;
	int pipe_fd[2];
	int prev_read_fd = -1;
	int cmd_count = 0;
	pid_t *pids = NULL;
	int i = 0;
	int status = 0;
	


	// Count commands
	for (t_cmd *tmp = cmd_list; tmp; tmp = tmp->next)
		cmd_count++;

	// Allocate PID array
	pids = ft_malloc(sizeof(pid_t) * cmd_count, 1);
	if (!pids)
		return;
	for (int j = 0; j < cmd_count; j++)
    	pids[j] = -1;

	cmd = cmd_list;
	while (cmd)
	{
		if (!cmd->args || !cmd->args[0])
		{
			cmd = cmd->next;
			continue;
		}

		if (cmd->pipe_after && pipe(pipe_fd) == -1)
		{
			perror("pipe");
			return;
		}

		// If it's a builtin and there's no pipe and no input redirection: run in parent
		if (is_builtin(cmd->args[0]) && !cmd->pipe_after && prev_read_fd == -1 && !cmd->infile)
		{
			mini->exit_status = run_builtin_no_pipe(cmd, mini);
		}
		else
		{
			pids[i] = fork();
			if (pids[i] == -1)
			{
				perror("fork");
				return;
			}
			if (pids[i] == 0) // Child
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
		{
			prev_read_fd = -1;
		}

		cmd = cmd->next;
		i++;
	}

	// Wait for all children
	for (int j = 0; j < i; j++)
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
	}
	//free(pids);
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
		close(pipe_fd[0]); // Close unused read end
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
}

#include <unistd.h>

void close_unused_fds(int *prev_read_fd, t_cmd *cmd, int pipe_fd[2])
{
    // Close old read end fd if still open
    if (*prev_read_fd != -1)
    {
        close(*prev_read_fd);
        *prev_read_fd = -1;
    }

    // Close write end of pipe in parent
    if (cmd->pipe_after)
    {
        close(pipe_fd[1]);
        *prev_read_fd = pipe_fd[0];
    }
}
#include <unistd.h>
#include <stdio.h>

int run_builtin_no_pipe(t_cmd *cmd, t_mini *mini)
{
    int saved_stdin = dup(STDIN_FILENO);
    int saved_stdout = dup(STDOUT_FILENO);
    int ret = 0;

    if (strcmp(cmd->args[0], "exit") == 0)
    {
        mini_exit(cmd, cmd->args, mini);
        return mini->exit_status; // or exit() internally
    }

    if (apply_redirections(cmd) != -1)
    {
        ret = exec_builtin(cmd->args, mini);
    }
    else
    {
        ret = 1; // redirection failed, set error status
    }

    // ALWAYS restore
    dup2(saved_stdin, STDIN_FILENO);
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdin);
    close(saved_stdout);

    mini->exit_status = ret;
    return ret;
}






#include <fcntl.h>
#include <unistd.h>

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h> // if using strerror
 // for ft_strlen, ft_putstr_fd

int	apply_redirections(t_cmd *cmd)
{
	int	fd;
	if(cmd->redirection_error == 1)
	{
		perror(cmd->infile ? cmd->infile : cmd->outfile);
		return (-1); // regular failure
	}

	// Input redirection: <
	if (cmd->infile)
	{
		fd = open(cmd->infile, O_RDONLY);
		if (fd == -1)
		{
			perror(cmd->infile);
			return (-1); // regular failure
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}

	// Output redirection: > or >>
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
