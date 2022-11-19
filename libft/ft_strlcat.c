/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 16:53:15 by mamartin          #+#    #+#             */
/*   Updated: 2020/09/18 17:44:10 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	len_dest;

	i = 0;
	j = 0;
	while (dst[i] != '\0' && i < size)
		i++;
	if (i == size)
		return (size + ft_strlen(src));
	len_dest = i;
	while (src[j] != '\0' && i < size - 1)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (len_dest + ft_strlen(src));
}
