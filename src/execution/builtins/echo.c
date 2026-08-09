/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghou <iel-ghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 08:35:34 by iel-ghou          #+#    #+#             */
/*   Updated: 2025/07/01 11:40:20 by iel-ghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

static int	is_all_n(const char *s)
{
	int	j;

	if (!s || s[0] != '-')
		return (0);
	j = 1;
	while (s[j])
	{
		if (s[j] != 'n')
			return (0);
		j++;
	}
	return (1);
}

int	ft_echo(char **args)
{
	int	i;
	int	n_option;

	i = 1;
	n_option = 0;
	while (args[i] && is_all_n(args[i]))
	{
		n_option = 1;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!n_option)
		write(1, "\n", 1);
	return (SUCCESS);
}
