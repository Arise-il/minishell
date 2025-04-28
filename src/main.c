/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouhlale <oouhlale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 09:03:46 by oouhlale          #+#    #+#             */
/*   Updated: 2025/04/28 09:53:38 by oouhlale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char	*input;
	t_cmd	*cmd_list;

	using_history();
	setup_signals();
	disable_ctrl_echo();
	rl_bind_key('\t', rl_complete);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (!*input || only_spaces(input) || check_unclosed_quotes(input))
		{
			free(input);
			continue ;
		}
		add_history(input);
		cmd_list = parse_input(input);
		free(input);
		free_cmd_list(cmd_list);
	}
	rl_clear_history();
	return (0);
}
