/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouhlale <oouhlale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 09:03:53 by oouhlale          #+#    #+#             */
/*   Updated: 2025/04/28 09:49:40 by oouhlale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define ECHOCTL 0001000
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>

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
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			**args;        // ["echo", "hello"]
	char			*infile;       // for `<` or `<<`
	char			*outfile;      // for `>` or `>>`
	int				append;       // 0: >, 1: >>
	int				heredoc;      // 1 if << used
	int				pipe_after;   // 1 if followed by pipe
	struct s_cmd	*next;
}	t_cmd;

void			setup_signals(void);
void			disable_ctrl_echo(void);
t_token			*new_token(char *value, t_token_type type);
void			add_token(t_token **head, t_token *new);
char			*extract_quoted(char *str, int *i);
char			*extract_word(char *str, int *i);
char			*extract_operator(const char *line, int *i);
t_token_type	get_token_type(char *value);
t_token			*tokenize_input(char *line);
int				check_unclosed_quotes(const char *input);
t_cmd			*build_command_table(t_token *tokens);
t_cmd			*parse_input(char *input);
void			free_tokens(t_token *tokens);
void			free_cmd_list(t_cmd *cmd_list);

#endif