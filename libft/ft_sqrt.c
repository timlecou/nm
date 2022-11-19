/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 21:11:58 by mamartin          #+#    #+#             */
/*   Updated: 2022/09/17 22:55:03 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

int	ft_sqrt(int nb)
{
	long	i;

	i = 2;
	if (nb == 1)
		return (1);
	if (nb % 2 == 1)
		i = 1;
	while (i <= nb / 2 + 1)
	{
		if (i * i == nb)
			return (i);
		i += 2;
	}
	return (0);
}

float ft_fsqrt(float number)
{
	long i = 0;
	float x2 = 0, y = 0;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = * ( long * ) &y;						// evil floating point bit level hacking
	i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration

	return ft_fabs(1 / y);
}
