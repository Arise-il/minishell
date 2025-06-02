/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghou <iel-ghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 08:35:42 by iel-ghou          #+#    #+#             */
/*   Updated: 2025/05/23 09:36:00 by iel-ghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../../includes/execution.h"

int		ft_env(t_env *env)
{
	while (env)
    {
        ft_putendl(env->value);
        env = env->next;
    }
    return (SUCCESS);
}
