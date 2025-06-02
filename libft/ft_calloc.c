/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouhlale <oouhlale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 12:41:45 by oouhlale          #+#    #+#             */
/*   Updated: 2025/05/31 09:45:54 by oouhlale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*tmp;

	tmp = ft_malloc(count * size, 1);
	if (!tmp)
	{
		return (NULL);
	}
	ft_bzero(tmp, (count * size));
	return (tmp);
}
