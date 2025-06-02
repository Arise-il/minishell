/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghou <iel-ghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 08:35:19 by iel-ghou          #+#    #+#             */
/*   Updated: 2025/05/23 09:36:12 by iel-ghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../../includes/execution.h"

int		ft_pwd(void)
{
	char	cwd[4096];

	if (getcwd(cwd, 4096))
	{
		ft_putendl_fd(cwd, 1);
		return (SUCCESS);
	}
	else
		return (ERROR);
}
