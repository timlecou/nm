/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 22:29:09 by mamartin          #+#    #+#             */
/*   Updated: 2020/09/18 22:30:55 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*cast_s;

	cast_s = (unsigned char *)s;
	while (n--)
	{
		*cast_s = '\0';
		cast_s++;
	}
}
