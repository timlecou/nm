/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 00:28:30 by mamartin          #+#    #+#             */
/*   Updated: 2020/11/21 19:45:54 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory.h"

static	int	sz_num(int n)
{
	if (n == 0)
		return (0);
	else
		return (sz_num(n / 10) + 1);
}

char		*ft_itoa(int n)
{
	int		size_n;
	long	nbr;
	char	*str;

	nbr = n;
	size_n = sz_num(nbr);
	if (nbr <= 0)
	{
		nbr *= -1;
		size_n++;
	}
	str = (char *)malloc(size_n + 1);
	if (!str)
		return (NULL);
	str[size_n] = '\0';
	while (size_n--)
	{
		str[size_n] = nbr % 10 + '0';
		nbr /= 10;
	}
	if (str[0] == '0' && n != 0)
		str[0] = '-';
	return (str);
}
