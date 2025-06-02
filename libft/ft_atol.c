/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghou <iel-ghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 08:12:22 by iel-ghou          #+#    #+#             */
/*   Updated: 2025/05/26 08:12:59 by iel-ghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atol(const char *str)
{
	int			i = 0;
	int			sign = 1;
	long long	num = 0;

	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;

	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;

	while (str[i] >= '0' && str[i] <= '9')
	{
		// Stop before overflow (optional)
		if (num > 922337203685477580 || (num == 922337203685477580 && str[i] - '0' > 7))
			break;
		num = num * 10 + (str[i++] - '0');
	}

	return (num * sign);
}
