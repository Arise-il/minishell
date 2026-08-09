/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghou <iel-ghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 09:03:53 by oouhlale          #+#    #+#             */
/*   Updated: 2025/07/03 14:45:19 by iel-ghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define ECHOCTL 0001000
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include "minishell.h"

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC
}	t_token_type;

typedef struct s_env
{
	char			*value;
	struct s_env	*next;
}				t_env;
typedef struct s_token
{
	char			*value;
	t_token_type	type;
	int				quoted;
	struct s_token	*next;
}	t_token;

typedef struct s_expand_data
{
	const char	*str;
	int			in_single;
	int			in_double;
	int			*i;
	t_env		*env;
	int			last_status;
}	t_expand_data;

typedef struct s_cmd
{
	char			**args;
	char			*infile;
	char			*outfile;
	int				infile_fd;
	int				outfile_fd;
	int				append;
	int				heredoc;
	int				redirection_error;
	int				is_interrupted;
	int				pipe_after;
	struct s_cmd	*next;
}	t_cmd;

void			setup_signals(void);
t_token			*new_token(char *value, t_token_type type, int quoted);
void			add_token(t_token **head, t_token *new);
char			*extract_word(char *line, int *i, int *was_quoted);
char			*extract_operator(const char *line, int *i);
t_token_type	get_token_type(char *value);
t_token			*tokenize_input(char *line);
int				check_unclosed_quotes(const char *input);
int				check_syntax(t_token *tokens);
char			*extract_var_name(const char *str, int *i);
char			*get_var_value(const char *name, t_env *env, int last_status);
char			*append_char(char *result, const char *str, int i);
char			*append_var(t_expand_data data, char *result);
void			expand_tokens(t_token **tokens, t_env *env, int last_status);
char			*handle_heredoc(char *delimiter, int quoted,
					t_expand_data *expand_data, int is_interrupted);
void			handle_redirection(t_cmd *cmd, t_token *token,
					t_env *env, int last_status);
t_cmd			*build_command_table(t_token *tokens,
					t_env *env, int last_status);
t_cmd			*parse_input(char *input, t_env *env, int last_exit_status);
void			*ft_malloc(size_t size, int flag);
void			handle_sigint(int sig);
void			handle_sigint_heredoc(int sig);

#endif