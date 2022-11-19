/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 17:34:03 by mamartin          #+#    #+#             */
/*   Updated: 2021/03/07 20:15:47 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory.h"

static void	clear(t_btree *root, void (*del)(void *))
{
	if (!root)
		return ;
	clear(root->left, del);
	clear(root->right, del);
	if (del)
		(*del)(root->item);
	free(root);
}

void		btree_clear(t_btree **root, void (*del)(void *))
{
	if (*root == NULL)
		return ;
	clear(*root, del);
	free(*root);
	*root = NULL;
}
