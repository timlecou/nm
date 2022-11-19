/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 14:42:30 by mamartin          #+#    #+#             */
/*   Updated: 2022/10/23 01:11:21 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory.h"
#include "math.h"

static int is_whitespace(char c)
{
	return ((c >= '\t' && c <= '\r') || c == ' ');
}

int ft_strtol(const char* nptr, long* value)
{
	int i;
	int sign = 1;
	long long nbr = 0;

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
		if (!ft_isdigit(nptr[i]))
			return -1; // invalid character found

		nbr = nbr * 10 + (nptr[i] - '0');
	}

	*value = nbr * sign;
	return 0;
}
