/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghou <iel-ghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 08:35:34 by iel-ghou          #+#    #+#             */
/*   Updated: 2025/05/24 10:04:27 by iel-ghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../../includes/execution.h"

int				ft_echo(char **args)
{
	int		i;
	int		n_option;

	i = 1;
	n_option = 0;
	
	// Check for -n options at the beginning
	while (args[i] && ft_strcmp(args[i], "-n") == 0)
	{
		n_option = 1;
		i++;
	}
	
	// Print remaining arguments
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])  // If there's a next argument, add space
			write(1, " ", 1);
		i++;
	}
	
	// Add newline unless -n option was used
	if (n_option == 0)
		write(1, "\n", 1);
	
	return (SUCCESS);
}
