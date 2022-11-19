/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 00:38:13 by mamartin          #+#    #+#             */
/*   Updated: 2022/10/02 09:55:12 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _OPT_TYPES_H_
# define _OPT_TYPES_H_

# include <stdint.h>
# include <stdbool.h>

/* Value types expected in a program/option parameter */
typedef enum e_paramtype
{
	PARAM_T_INT64,
	PARAM_T_FLOAT64,
	PARAM_T_STRING
} t_paramtype;

/* Types of arguments returned */
typedef enum e_argtype
{
	ARG_T_OPTION,
	ARG_T_PARAMETER,
	ARG_T_ERROR,
} t_argtype;

/* Option parser error codes */
typedef enum e_errtype
{
	ERR_NONE,
	ERR_BAD_OPTION,
	ERR_MISSING_PARAM,
	ERR_BAD_PARAM_TYPE
} t_errtype;

/* Structure returned when argtype = ARG_T_OPTION */
struct s_optinfo
{
	char name;
	void* value;
};

/* Structure returned when argtype = ARG_T_PARAMETER */
struct s_paraminfo
{
	void* value;
};

/* Structure returned when argtype = ARG_T_ERROR */
struct s_errinfo
{
	char name;
	t_errtype type;
};

/* Describe expected options in arguments */
typedef struct s_expected_opts
{
	char name;
	bool has_param;
	t_paramtype paramtype;
} t_expected_opts;

/* Describe an argument returned after parsing */
typedef struct s_argument
{
	char name;
	void *value;
	t_argtype type;
	t_errtype errtype;
} t_argument;

#endif
