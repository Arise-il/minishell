/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouhlale <oouhlale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 09:03:46 by oouhlale          #+#    #+#             */
/*   Updated: 2025/04/20 23:49:45 by oouhlale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char	*input;

	rl_bind_key('\t', rl_complete);
	using_history();
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input == '\0' || only_spaces(input))
			continue ;
		printf("Input: %s\n", input);
		add_history(input);
		free(input);
		rl_clear_history();
	}
	return (0);
}
