/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 23:58:34 by mamartin          #+#    #+#             */
/*   Updated: 2021/03/06 00:04:54 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory.h"

t_list	*ft_lstdup(t_list *src, int length)
{
	t_list	*cpy;
	t_list	*lst;
	int		i;

	i = 0;
	cpy = NULL;
	while (src && i < length)
	{
		lst = ft_lstnew(src->content);
		if (!lst)
		{
			ft_lstclear(&cpy, NULL);
			return (NULL);
		}
		ft_lstadd_back(&cpy, lst);
		src = src->next;
		i++;
	}
	return (cpy);
}
