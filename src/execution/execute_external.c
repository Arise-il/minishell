/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghou <iel-ghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 18:40:26 by iel-ghou          #+#    #+#             */
/*   Updated: 2025/06/27 17:08:47 by iel-ghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

void	handle_exec_error(char *cmd_name, int err)
{
	if (err == ENOENT)
		fprintf(stderr, "%s: command not found\n", cmd_name);
	else if (err == EACCES)
		fprintf(stderr, "%s: Permission denied\n", cmd_name);
	else
		perror("minishell");
	ft_malloc(0, 0);
	if (err == EACCES)
		exit(126);
	exit(127);
}

void	handle_path_command(t_cmd *cmd, char **envp)
{
	if (access(cmd->args[0], F_OK) == 0)
	{
		if (access(cmd->args[0], X_OK) == 0)
			execve(cmd->args[0], cmd->args, envp);
		perror(cmd->args[0]);
		ft_malloc(0, 0);
		exit(126);
	}
	fprintf(stderr, "%s: No such file or directory\n", cmd->args[0]);
	ft_malloc(0, 0);
	exit(127);
}

int	handle_if_path_is_directory(t_cmd *cmd)
{
	struct stat	st;

	if (strchr(cmd->args[0], '/')
		&& stat(cmd->args[0], &st) == 0
		&& S_ISDIR(st.st_mode))
	{
		fprintf(stderr, "%s: Is a directory\n", cmd->args[0]);
		ft_malloc(0, 0);
		return (1);
	}
	return (0);
}

void	execute_external(t_cmd *cmd, t_env *env)
{
	char	**envp;
	char	*path;

	if (handle_if_path_is_directory(cmd))
		exit(126);
	envp = env_to_array(env);
	path = get_env_value("PATH", env);
	if (!path || !*path)
	{
		if (!strchr(cmd->args[0], '/'))
		{
			fprintf(stderr, "minishell: ");
			fprintf(stderr, "%s: No such file or directory\n", cmd->args[0]);
			ft_malloc(0, 0);
			exit(127);
		}
	}
	if (strchr(cmd->args[0], '/'))
		handle_path_command(cmd, envp);
	else
		execvp(cmd->args[0], cmd->args);
	handle_exec_error(cmd->args[0], errno);
}
