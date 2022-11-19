/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 18:59:02 by mamartin          #+#    #+#             */
/*   Updated: 2020/11/19 00:02:33 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*cast_s;
	unsigned char	to_find;
	size_t			i;

	i = 0;
	to_find = (unsigned char)c;
	cast_s = (unsigned char *)s;
	while (i < n)
	{
		if (cast_s[i] == to_find)
			return (cast_s + i);
		i++;
	}
	return (NULL);
}
