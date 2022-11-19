/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_diux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 19:12:09 by mamartin          #+#    #+#             */
/*   Updated: 2022/09/17 23:19:11 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "mandatory.h"
#include "utils.h"

int		print_int(t_flags flags, va_list ap)
{
	int		nb;
	size_t	size;
	char	*str;

	nb = va_arg(ap, int);
	if (flags.precision == 0 && nb == 0)
	{
		print_blanks(0, flags, 0);
		return (get_nb_char_printed(0, flags.width));
	}
	str = convert_int(flags, nb);
	if (!str)
		return (-1);
	size = ft_strlen(str);
	print(str, size, flags, 0);
	free(str);
	return (get_nb_char_printed(size, flags.width));
}

char	*convert_int(t_flags flags, int nb)
{
	char	*str;

	str = ft_itoa(nb);
	if (!str)
		return (NULL);
	if (!add_zeros(&str, flags.precision))
		return (NULL);
	if (nb < 0)
	{
		ft_memset(ft_strchr(str, '-'), '0', 1);
		str[0] = '-';
	}
	return (str);
}

int		print_uint(t_flags flags, va_list ap)
{
	unsigned int	nb;
	size_t			size;
	char			*str;

	nb = va_arg(ap, unsigned int);
	if (flags.precision == 0 && nb == 0)
	{
		print_blanks(0, flags, 0);
		return (get_nb_char_printed(0, flags.width));
	}
	str = convert_uint(flags, nb);
	if (!str)
		return (-1);
	size = ft_strlen(str);
	print(str, size, flags, 0);
	free(str);
	return (get_nb_char_printed(size, flags.width));
}

char	*convert_uint(t_flags flags, unsigned int nb)
{
	char *str;

	str = NULL;
	if (flags.type == 'u')
		str = ft_itoa_base(nb, "0123456789");
	else if (flags.type == 'x')
		str = ft_itoa_base(nb, "0123456789abcdef");
	else if (flags.type == 'X')
		str = ft_itoa_base(nb, "0123456789ABCDEF");
	if (!str)
		return (NULL);
	if (!add_zeros(&str, flags.precision))
		return (NULL);
	return (str);
}
