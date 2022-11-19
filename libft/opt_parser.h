/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 00:24:30 by mamartin          #+#    #+#             */
/*   Updated: 2022/09/22 16:06:58 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _OPT_PARSER_
# define _OPT_PARSER_

# include "opt_types.h"

/*
** Parse command-line arguments
**
** @param	argc		count of arguments (as in main function)
** @param	argv		array of arguments (as in main function)
** @param	options		array of accepted options in arguments
** @param	count		size of options array
** @param	arg			pointer to a t_argument where to store the result
**
** @return	0 in case of success, -1 when there is no argument left to parse
*/
int ft_getarg(int argc, char** argv, t_expected_opts* options, int count, t_argument* arg);

/*
** Find option
**
** @param	optname		name of the option to look for
** @param	options		array of valid options
** @param	count		size of options array
**
** @return	a pointer to the option or NULL if optname does not match any option
*/
t_expected_opts* find_option(char optname, t_expected_opts* options, int count);

/*
** Convert parameter from a string format into the type requested
**
** @param	str			string representing the parameter value
** @param	value		type of value to convert to
**
** @return	a pointer to the newly allocated data or NULL if it fails
*/
void* parse_option_parameter(const char* str, t_paramtype type);

void jump_to_next_arg(int* arg, int* character);
void set_error(t_argument* arg, t_errtype type, char name, void* value);

#endif
