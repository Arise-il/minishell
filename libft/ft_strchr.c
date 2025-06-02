/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouhlale <oouhlale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:23:04 by oouhlale          #+#    #+#             */
/*   Updated: 2024/11/11 13:16:51 by oouhlale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	to_find;
	int		i;

	to_find = (char) c;
	i = 0;
	while (s[i])
	{
		if (s[i] == to_find)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	if (s[i] == to_find)
	{
		return ((char *)&s[i]);
	}
	return (NULL);
}
