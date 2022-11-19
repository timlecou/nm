/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 17:49:40 by mamartin          #+#    #+#             */
/*   Updated: 2020/11/21 17:38:52 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory.h"

char	*ft_strchr(const char *s, int c)
{
	char	*s_noconst;
	char	to_find;
	int		i;

	i = 0;
	s_noconst = (char *)s;
	to_find = (char)c;
	while (s[i] != '\0' && s[i] != to_find)
		i++;
	if (s[i] == to_find && s[i])
		return (s_noconst + i);
	else
		return (NULL);
}
