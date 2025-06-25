/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghou <iel-ghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 08:26:48 by iel-ghou          #+#    #+#             */
/*   Updated: 2025/06/25 17:22:07 by iel-ghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
#include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <sys/stat.h>


# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define SKIP 1
# define NOSKIP 0

# define BUFF_SIZE 4096
# define EXPANSION -36
# define ERROR 1
# define SUCCESS 0
# define IS_DIRECTORY 126
# define UNKNOWN_COMMAND 127
# define LLONG_MAX_STR 9223372036854775807


int		exec_builtin(char **args, t_mini *mini);
int		is_builtin(char *command);
void	execute_commands(t_cmd *cmd_list, t_mini *mini);

// BUILTINS
int			ft_cd(char **args, t_env *env);
int			ft_echo(char **args);
int		    ft_env(t_env *env);
void	mini_exit(t_cmd *cmd, char **args, t_mini *mini);
int			ft_export(char **args, t_env *env);
int ft_pwd(t_env *env);
int				ft_unset(char **a, t_mini *mini);

//env
int				secret_env_init(t_mini *mini, char **env_array);
char	*get_env_value(char *arg, t_env *env);
void				increment_shell_level(t_env *env);
void		print_sorted_env(t_env *env);
int	env_init(t_mini *mini, char **env_array);
char	*env_to_str(t_env *lst);
size_t	size_env(t_env *lst);

int			env_add(const char *value, t_env *env);
int			is_in_env(t_env *env, char *args);
int		is_valid_env(const char *env);
int			is_in_env(t_env *env, char *args);
char		*get_env_name(char *dest, const char *src);
char			*env_to_str(t_env *lst);

void	setup_pipes(t_cmd *cmd, int prev_read_fd, int pipe_fd[2]);
void	close_unused_fds(int *prev_read_fd, t_cmd *cmd, int pipe_fd[2]);
int 	run_builtin_no_pipe(t_cmd *cmd, t_mini *mini);

int	apply_redirections(t_cmd *cmd);
int	env_update(char *new_value, t_env *env);

#endif