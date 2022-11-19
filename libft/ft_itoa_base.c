/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 20:50:45 by mamartin          #+#    #+#             */
/*   Updated: 2022/09/17 22:51:14 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "utils.h"

static	int	sz_num(unsigned long long n, int base)
{
	if (n == 0)
		return (0);
	else
		return (sz_num(n / base, base) + 1);
}

static int	check_base(char *base)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (base == 0 || base[0] == '\0' || base[1] == '\0')
		return (0);
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-')
			return (0);
		while (base[j])
		{
			if (base[j] == base[i] && j != i)
				return (0);
			j++;
		}
		j = i;
		i++;
	}
	return (i);
}

char		*ft_itoa_base(unsigned long long nbr, char *base)
{
	int		size_n;
	int		size_base;
	char	*str;

	size_base = check_base(base);
	if (!size_base)
		return (NULL);
	size_n = sz_num(nbr, size_base);
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
		str[size_n] = base[nbr % size_base];
		nbr /= size_base;
	}
	if (str[0] == base[0] && nbr != 0)
		str[0] = '-';
	return (str);
}
