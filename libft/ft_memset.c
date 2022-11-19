/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 14:57:50 by mamartin          #+#    #+#             */
/*   Updated: 2020/11/19 00:03:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*cast_s;
	size_t			i;

	i = 0;
	if (n < 1)
		return (s);
	cast_s = (unsigned char *)s;
	while (i < n)
	{
		cast_s[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
