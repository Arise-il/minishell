/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouhlale <oouhlale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 10:45:52 by oouhlale          #+#    #+#             */
/*   Updated: 2025/06/01 14:44:02 by oouhlale         ###   ########.fr       */
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
	close(fd); // We'll open it again ourselves
	return (template); // Caller must free it later
}

char	*handle_heredoc(char *delimiter, int quoted, t_expand_data *expand_data)
{
	char	*line;
	char	*expanded;
	char	*tmp_filename;
	int		fd;

	tmp_filename = generate_unique_tmpname();
	fd = open(tmp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (perror("open"), NULL);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
			break ;
		if (!quoted)
			expanded = expand_token_string(line, expand_data->env, expand_data->last_status);
		else
			expanded = ft_strdup(line);
		write(fd, expanded, ft_strlen(expanded));
		write(fd, "\n", 1);
	}
	close(fd);
	return (tmp_filename);
}
