/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <mamartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 14:48:29 by user42            #+#    #+#             */
/*   Updated: 2020/11/23 15:03:15 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*curr;

	curr = *lst;
	while (curr)
	{
		tmp = curr->next;
		if (del)
			(*del)(curr->content);
		free(curr);
		curr = tmp;
	}
	*lst = NULL;
}
