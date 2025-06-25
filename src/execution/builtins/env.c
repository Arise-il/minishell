/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghou <iel-ghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 08:35:42 by iel-ghou          #+#    #+#             */
/*   Updated: 2025/06/25 16:31:57 by iel-ghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

int	ft_env(t_env *env)
{
	while (env)
	{
		if (ft_strchr(env->value, '='))
			ft_putendl_fd(env->value, STDOUT_FILENO);
		env = env->next;
	}
	return (SUCCESS);
}
