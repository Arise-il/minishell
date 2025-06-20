/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghou <iel-ghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 08:35:42 by iel-ghou          #+#    #+#             */
/*   Updated: 2025/06/20 15:06:42 by iel-ghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../../includes/execution.h"

int		ft_env(t_env *env)
{
	while (env)
    {
        if (ft_strchr(env->value, '='))  // only vars with '='
            ft_putendl_fd(env->value, STDOUT_FILENO);
        env = env->next;
    }
    return (SUCCESS);
}
