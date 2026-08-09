/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouhlale <oouhlale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 10:45:52 by oouhlale          #+#    #+#             */
/*   Updated: 2025/07/01 15:35:44 by oouhlale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*expand_token_string(const char *str, t_env *env, int last_status)
{
	t_expand_data	data;
	char			*result;
	int				i;

	data.str = str;
	data.i = &i;
	data.env = env;
	data.last_status = last_status;
	i = 0;
	result = ft_calloc(1, 1);
	while (str[i])
	{
		if (str[i] == '$')
		{
			result = append_var(data, result);
			continue ;
		}
		else
			result = append_char(result, str, i);
		i++;
	}
	return (result);
}

char	*generate_unique_tmpname(void)
{
	char	*template;
	int		fd;

	template = ft_strdup("/tmp/.heredoc_XXXXXX");
	fd = mkstemp(template);
	if (fd == -1)
		return (NULL);
	close(fd);
	return (template);
}

static void	heredoc_child_process(char *filename, char *delimiter,
		int quoted, t_expand_data *expand_data)
{
	char	*line;
	char	*expanded;
	int		fd;

	signal(SIGINT, handle_sigint_heredoc);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		exit(1);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
			break ;
		if (!quoted)
			expanded = expand_token_string(line, expand_data->env,
					expand_data->last_status);
		else
			expanded = ft_strdup(line);
		write(fd, expanded, ft_strlen(expanded));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	close(fd);
	exit(0);
}

static int	heredoc_wait_and_check(char *filename)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	waitpid(-1, &status, 0);
	signal(SIGINT, handle_sigint);
	if ((WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		|| (WIFEXITED(status) && WEXITSTATUS(status) == 130))
	{
		unlink(filename);
		return (1);
	}
	return (0);
}

char	*handle_heredoc(char *delimiter, int quoted,
		t_expand_data *expand_data, int is_interrupted)
{
	char	*tmp_filename;
	pid_t	pid;

	if (is_interrupted)
		return (NULL);
	tmp_filename = generate_unique_tmpname();
	pid = fork();
	if (pid == 0)
		heredoc_child_process(tmp_filename, delimiter, quoted, expand_data);
	if (heredoc_wait_and_check(tmp_filename))
		return (NULL);
	return (tmp_filename);
}
