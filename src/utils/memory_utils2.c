/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouhlale <oouhlale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 09:39:59 by oouhlale          #+#    #+#             */
/*   Updated: 2025/06/01 14:30:07 by oouhlale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}

void	*ft_malloc(size_t size, int flag)
{
	void	*p;
	static	t_list *data;
	t_list	*node;

	p = NULL;
	node = NULL;
	if (flag == 0)
	{
		while (data)
		{
			node = data;
			data = data->next;
			free(node->content);
			free(node);
		}
		return (NULL);
	}
	p = malloc(size);
	if (!p)
	{
		return (NULL);
	}
	node = ft_lstnew(p);
	ft_lstadd_front(&data ,node);
	return (p);
}

