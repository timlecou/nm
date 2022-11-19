/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 21:32:51 by mamartin          #+#    #+#             */
/*   Updated: 2020/11/21 18:42:17 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	j = 0;
	str = (char *)big;
	if (ft_strlen(little) == 0)
		return (str);
	while (*str != '\0')
	{
		i = 0;
		while (str[i] == little[i] && little[i] && i + j < len)
			i++;
		if (little[i] == '\0')
			return (str);
		str++;
		j++;
	}
	return (NULL);
}
