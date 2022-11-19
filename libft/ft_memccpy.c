/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 18:00:31 by mamartin          #+#    #+#             */
/*   Updated: 2020/11/19 00:02:25 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*cast_dest;
	unsigned char	*cast_src;
	unsigned char	to_find;
	size_t			i;

	i = 0;
	to_find = (unsigned char)c;
	cast_dest = (unsigned char *)dest;
	cast_src = (unsigned char *)src;
	while (i < n)
	{
		cast_dest[i] = cast_src[i];
		if (cast_src[i] == to_find)
			return (dest + i + 1);
		i++;
	}
	return (NULL);
}
