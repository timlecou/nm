/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:49:32 by mamartin          #+#    #+#             */
/*   Updated: 2022/09/17 23:05:08 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "mandatory.h"

void	print(char *str, size_t size, t_flags flags, char blank)
{
	int	is_minus_printed;

	is_minus_printed = 0;
	if (str[0] == '-' && flags.precision == -1 && ft_strchr("di", flags.type))
	{
		if (flags.is_0_padded && !flags.is_left_adjusted)
		{
			ft_putchar_fd('-', 1);
			ft_strlcpy(str, str + 1, ft_strlen(str));
			is_minus_printed = 1;
		}
	}
	if (!flags.is_left_adjusted)
		print_blanks(size, flags, blank);
	write(1, str, size - is_minus_printed);
	if (flags.is_left_adjusted)
		print_blanks(size, flags, blank);
}

int		add_zeros(char **str, int precision)
{
	int		size;
	char	*zeros;
	char	*tmp;

	size = ft_strlen(*str);
	if ((*str)[0] == '-')
		size--;
	if (size >= precision)
		return (1);
	size = precision - size;
	zeros = (char *)ft_calloc(size + 1, 1);
	if (!zeros)
		return (0);
	ft_memset(zeros, '0', size);
	tmp = *str;
	*str = ft_strjoin(zeros, *str);
	free(zeros);
	free(tmp);
	if (!(*str))
		return (0);
	return (1);
}

void	print_blanks(size_t size, t_flags flags, char blank)
{
	if ((int)size >= flags.width)
		return ;
	if (blank == 0)
	{
		blank = ' ';
		if (flags.precision == -1)
		{
			if (flags.is_0_padded && !flags.is_left_adjusted)
				blank = '0';
		}
	}
	while ((int)size < flags.width)
	{
		ft_putchar_fd(blank, 1);
		size++;
	}
}

int		get_nb_char_printed(size_t size, int width)
{
	if ((int)size >= width)
		return ((int)size);
	else
		return (width);
}
