/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:48:54 by mamartin          #+#    #+#             */
/*   Updated: 2022/09/17 22:38:34 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FT_PRINTF_H_
# define _FT_PRINTF_H_

# include <stdlib.h>
# include <stdarg.h>

typedef struct	s_flags
{
	int		is_0_padded;
	int		is_left_adjusted;
	int		width;
	int		precision;
	char	type;
	int		size;
}				t_flags;

int				ft_printf(const char *format, ...);
int				convert_arg(const char *format, va_list ap, int *i, int *size);
int				print_arg(t_flags flags, va_list ap);

t_flags			read_flags(const char *str, va_list ap);
void			init_struct_flags(t_flags *flags);
int				get_precision(const char *str, va_list ap);
int				get_width(const char *str, va_list ap);

void			print(char *str, size_t size, t_flags flags, char blank);
int				add_zeros(char **str, int precision);
void			print_blanks(size_t size, t_flags flags, char blank);
int				get_nb_char_printed(size_t size, int width);

int				print_int(t_flags flags, va_list ap);
char			*convert_int(t_flags flags, int nb);
int				print_uint(t_flags flags, va_list ap);
char			*convert_uint(t_flags flags, unsigned int nb);

int				print_str(t_flags flags, va_list ap);
int				print_ptr(t_flags flags, va_list ap);
int				print_null_ptr(t_flags flags);
int				print_char(t_flags flags, va_list ap);

#endif
