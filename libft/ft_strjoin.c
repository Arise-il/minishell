/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouhlale <oouhlale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:15:13 by oouhlale          #+#    #+#             */
/*   Updated: 2025/05/31 09:46:38 by oouhlale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*concat;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	concat = ft_malloc(ft_strlen(s1) + ft_strlen(s2) + 1, 1);
	if (concat == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		concat[j++] = s1[i++];
	}
	i = 0;
	while (s2[i])
	{
		concat[j++] = s2[i++];
	}
	concat[j] = '\0';
	return (concat);
}
