/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_csp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 23:27:41 by mamartin          #+#    #+#             */
/*   Updated: 2022/09/17 23:19:02 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "mandatory.h"
#include "utils.h"

int	print_str(t_flags flags, va_list ap)
{
	const char	*str;
	size_t		size;

	str = va_arg(ap, const char *);
	if (flags.precision == 0)
	{
		print_blanks(0, flags, ' ');
		return (get_nb_char_printed(0, flags.width));
	}
	if (str == NULL)
		str = "(null)";
	size = ft_strlen(str);
	if ((int)size > flags.precision && flags.precision != -1)
		size = flags.precision;
	print((char *)str, size, flags, ' ');
	return (get_nb_char_printed(size, flags.width));
}

int	print_ptr(t_flags flags, va_list ap)
{
	void	*ptr;
	char	*str;
	char	*tmp;
	size_t	size;

	ptr = va_arg(ap, void *);
	if (ptr == NULL)
		return (print_null_ptr(flags));
	str = ft_itoa_base((unsigned long long)ptr, "0123456789abcdef");
	if (!str)
		return (-1);
	tmp = str;
	str = ft_strjoin("0x", str);
	free(tmp);
	if (!str)
		return (-1);
	size = ft_strlen(str);
	print(str, size, flags, ' ');
	free(str);
	return (get_nb_char_printed(size, flags.width));
}

int	print_null_ptr(t_flags flags)
{
	char	*str;
	size_t	size;

	if (flags.precision == -1)
		str = "0x0";
	else
		str = "0x";
	size = ft_strlen(str);
	if (!flags.is_left_adjusted)
		print_blanks(size, flags, ' ');
	ft_putstr_fd(str, 1);
	if (flags.is_left_adjusted)
		print_blanks(size, flags, ' ');
	return (get_nb_char_printed(size, flags.width));
}

int	print_char(t_flags flags, va_list ap)
{
	unsigned char	c;

	c = (unsigned char)va_arg(ap, int);
	if (!flags.is_left_adjusted)
		print_blanks(1, flags, ' ');
	ft_putchar_fd(c, 1);
	if (flags.is_left_adjusted)
		print_blanks(1, flags, ' ');
	return (get_nb_char_printed(1, flags.width));
}
