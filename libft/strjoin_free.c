/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouhlale <oouhlale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:16:04 by oouhlale          #+#    #+#             */
/*   Updated: 2025/05/13 09:59:03 by oouhlale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*strjoin_free(char *s1, const char *s2)
{
	char *tmp = ft_strjoin(s1, s2);
	free(s1);
	return (tmp);
}
