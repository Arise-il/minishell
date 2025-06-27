/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghou <iel-ghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 09:03:58 by oouhlale          #+#    #+#             */
/*   Updated: 2025/06/26 15:41:30 by iel-ghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include "../libft/libft.h"

typedef struct s_list
{
	void	*content;
	struct  s_list *next;
} t_list;

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	int				quoted;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			**args;        // ["echo", "hello"]
	char			*infile;       // for `<` or `<<`
	char			*outfile;      // for `>` or `>>`
	int				infile_fd;
	int				outfile_fd;
	int				append;       // 0: >, 1: >>
	int				heredoc;      // 1 if << used
	int				redirection_error;
	int				pipe_after;   // 1 if followed by pipe
	struct s_cmd	*next;
}	t_cmd;

typedef struct	s_env
{
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_expand_data {
	const char	*str;
	int			*i;
	t_env		*env;
	int			last_status;
}	t_expand_data;

typedef struct s_mini {
	t_env	*env;
	t_env	*secret_env;
	int exit_status; 
	t_cmd	*cmds;
	t_cmd	*current_cmd;
}	t_mini;

# include "parser.h"
# include "execution.h"

#endif