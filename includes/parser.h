/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouhlale <oouhlale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 09:03:53 by oouhlale          #+#    #+#             */
/*   Updated: 2025/04/22 15:52:38 by oouhlale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define ECHOCTL 0001000
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>

typedef struct s_token
{
	char			*value;
	struct s_token	*next;
}	t_token;

t_token	*tokenize_input(char *line);

void	setup_signals(void);
void	disable_ctrl_echo(void);
t_token	*new_token(char *value);
void	add_token(t_token **head, t_token *new);
char	*extract_quoted(char *str, int *i);
char	*extract_word(char *str, int *i);
t_token	*tokenize_input(char *line);
void	parse_input(char *input);

#endif