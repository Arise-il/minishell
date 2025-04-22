/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouhlale <oouhlale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:03:44 by oouhlale          #+#    #+#             */
/*   Updated: 2025/04/22 15:51:52 by oouhlale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parse_input(char *input)
{
	t_token	*tokens;
	t_token	*tmp;

	tokens = tokenize_input(input);
	tmp = tokens;
	while (tmp)
	{
		printf("Token: [%s]\n", tmp->value);
		tmp = tmp->next;
	}
}
