/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouhlale <oouhlale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 09:03:53 by oouhlale          #+#    #+#             */
/*   Updated: 2025/04/25 08:49:49 by oouhlale         ###   ########.fr       */
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
void			parse_input(char *input);
void			free_tokens(t_token *tokens);

#endif