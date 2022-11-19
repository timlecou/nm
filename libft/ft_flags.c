/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:49:08 by mamartin          #+#    #+#             */
/*   Updated: 2022/09/17 23:05:11 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "mandatory.h"

t_flags	read_flags(const char *str, va_list ap)
{
	int		i;
	t_flags	flags;

	i = 0;
	init_struct_flags(&flags);
	while (str[i] == '0' || str[i] == '-')
	{
		if (str[i] == '0')
			flags.is_0_padded = 1;
		else if (str[i] == '-')
			flags.is_left_adjusted = 1;
		i++;
	}
	flags.width = get_width(str + i, ap);
	if (flags.width < 0)
	{
		flags.width = -flags.width;
		flags.is_left_adjusted = 1;
	}
	flags.precision = get_precision(str + i, ap);
	while (!ft_isalpha(str[i]) && str[i] != '%' && str[i])
		i++;
	flags.type = str[i];
	flags.size = i + 1;
	return (flags);
}

void	init_struct_flags(t_flags *flags)
{
	flags->is_0_padded = 0;
	flags->is_left_adjusted = 0;
	flags->width = 0;
	flags->precision = 0;
	flags->type = 0;
	flags->size = 0;
}

int		get_precision(const char *str, va_list ap)
{
	int	i;

	i = 0;
	while (!ft_isalpha(str[i]) && str[i] != '%' && str[i])
	{
		if (str[i] == '.')
		{
			if (str[i + 1] == '*')
				return (va_arg(ap, int));
			else
				return (ft_atoi(str + i + 1));
		}
		i++;
	}
	return (-1);
}

int		get_width(const char *str, va_list ap)
{
	if (*str == '*')
		return (va_arg(ap, int));
	else
		return (ft_atoi(str));
}
