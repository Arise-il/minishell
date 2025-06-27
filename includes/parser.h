/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghou <iel-ghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 09:03:53 by oouhlale          #+#    #+#             */
/*   Updated: 2025/06/27 19:18:53 by iel-ghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define ECHOCTL 0001000
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include "minishell.h"

void			setup_signals(void);
void			disable_ctrl_echo(void);
t_token			*new_token(char *value, t_token_type type, int quoted);
void			add_token(t_token **head, t_token *new);
char			*extract_word(char *line, int *i, int *was_quoted);
char			*extract_operator(const char *line, int *i);
t_token_type	get_token_type(char *value);
t_token			*tokenize_input(char *line);
int				check_unclosed_quotes(const char *input);
int				check_syntax(t_token *tokens);
char			*extract_var_name(const char *str, int *i);
char 			*get_var_value(const char *name, t_env *env, int last_status);
char			*append_char(char *result, const char *str, int i);
char			*append_var(t_expand_data data, char *result);
void 			expand_tokens(t_token **tokens, t_env *env, int last_status);
char			*handle_heredoc(char *delimiter, int quoted, t_expand_data *expand_data);
t_cmd			*build_command_table(t_token *tokens, t_env *env, int last_status);
t_cmd			*parse_input(char *input, t_env *env, int last_exit_status);
void			*ft_malloc(size_t size, int flag);
void	handle_sigint(int sig);
void	handle_sigint_heredoc(int sig);
void			free_tokens(t_token *tokens);
void			free_cmd_list(t_cmd *cmd_list);
void			free_2d(char **arr);
void			free_str_array(char **arr);
void print_cmds(t_cmd *cmd);

#endif