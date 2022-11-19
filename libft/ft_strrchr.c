/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 17:49:40 by mamartin          #+#    #+#             */
/*   Updated: 2020/11/19 00:04:25 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*s_noconst;
	char	to_find;
	int		i;

	i = ft_strlen(s);
	s_noconst = (char *)s;
	to_find = (char)c;
	while (i >= 0)
	{
		if (s[i] == to_find)
			return (s_noconst + i);
		i--;
	}
	return (NULL);
}
