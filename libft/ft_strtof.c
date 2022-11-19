/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtof.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 14:43:47 by mamartin          #+#    #+#             */
/*   Updated: 2022/10/23 01:12:08 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "mandatory.h"
#include "math.h"

static int is_whitespace(char c)
{
	return ((c >= '\t' && c <= '\r') || c == ' ');
}

int ft_strtof(const char* nptr, double* value)
{
	int i;
	int sign = 1;
	double decimal_factor = 1;
	long double nbr = 0;

	/* Ignore whitespace at the beginning of the string */
	for (i = 0; is_whitespace(nptr[i]); i++);

	/* Handle sign operators */
	if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;

	/* Check the string is not juste whitespaces and a sign operator */
	if (nptr[i] == '\0')
		return -1;

	for (i = (int)i; nptr[i]; i++) // i = (int)i is to avoid a stupid warning
	{
		if (nptr[i] == '.')
		{
			if (decimal_factor != 1)
				return -1; // multiple dots found in string
			decimal_factor = 10;
		}
		else if (!ft_isdigit(nptr[i]))
			return -1; // invalid character found
		else
		{
			if (decimal_factor == 1)
				nbr = nbr * 10.0 + (nptr[i] - '0');
			else
			{
				nbr = nbr + (nptr[i] - '0') / decimal_factor;
				decimal_factor *= 10;
			}
		}
	}

	*value = nbr * sign;
	return 0;
}
