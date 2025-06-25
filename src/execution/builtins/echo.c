/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghou <iel-ghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 08:35:34 by iel-ghou          #+#    #+#             */
/*   Updated: 2025/06/25 16:31:50 by iel-ghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

int	ft_echo(char **args)
{
	int		i;
	int		n_option;

	i = 1;
	n_option = 0;
	while (args[i] && ft_strcmp(args[i], "-n") == 0)
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
	if (n_option == 0)
		write(1, "\n", 1);
	return (SUCCESS);
}
