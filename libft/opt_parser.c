/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 04:08:52 by mamartin          #+#    #+#             */
/*   Updated: 2022/10/23 01:09:56 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include "opt_parser.h"
#include "mandatory.h"
#include "math.h"

int ft_getarg(int argc, char** argv, t_expected_opts* options, int count, t_argument* arg)
{
	static int argidx = 1;
	static int charidx = 0;

	char* curr;
	t_expected_opts* opt;

	if (argidx >= argc)
		return -1;

	if (!argv[argidx][charidx])
		jump_to_next_arg(&argidx, &charidx);
	if (argidx >= argc)
		return -1;

	arg->errtype = ERR_NONE;
	curr = argv[argidx];
	if (charidx == 0)
	{
		if (curr[0] == '-') // it's an option
			charidx = 1;
		else // it's a program parameter
		{
			arg->type = ARG_T_PARAMETER;
			arg->value = curr;
			jump_to_next_arg(&argidx, &charidx);
			return 0;
		}
	}

	if (!(opt = find_option(curr[charidx], options, count)))
		set_error(arg, ERR_BAD_OPTION, curr[charidx], NULL);
	else
	{
		arg->type = ARG_T_OPTION;
		arg->name = opt->name;

		if (opt->has_param)
		{
			char* parameter = NULL;

			if (ft_strlen(curr) != (unsigned int)(charidx + 1)) // take value from what's left of the current string
				parameter = curr + charidx + 1;
			else
			{
				if (++argidx < argc) // take value from the next argument string
					parameter = argv[argidx];
				else
				{
					set_error(arg, ERR_MISSING_PARAM, opt->name, NULL);
					return 0;
				}
			}
			
			arg->value = parse_option_parameter(parameter, opt->paramtype);
			if (!arg->value)
			{
				if (errno == ENOMEM)
					return -2;
				set_error(arg, ERR_BAD_PARAM_TYPE, opt->name, parameter);
			}

			jump_to_next_arg(&argidx, &charidx);
		}
		else
		{
			arg->value = NULL;
			charidx++;
		}
	}

	return 0;
}

t_expected_opts* find_option(char optname, t_expected_opts* options, int count)
{
	int i;

	for (i = 0; i < count; i++)
	{
		if (options[i].name == optname)
			return options + i;
	}
	return NULL;
}

void* parse_option_parameter(const char* str, t_paramtype type)
{
	void* ptr;

	switch (type)
	{
		case PARAM_T_INT64:
			ptr = malloc(sizeof(int64_t));
			if (!ptr)
				return NULL;
			if (ft_strtol(str, ptr) != 0)
			{
				free(ptr);
				return NULL;
			}
			return ptr;
		case PARAM_T_FLOAT64:
			ptr = malloc(sizeof(double));
			if (!ptr)
				return NULL;
			if (ft_strtof(str, ptr) != 0)
			{
				free(ptr);
				return NULL;
			}
			return ptr;
		case PARAM_T_STRING:
			return ft_strdup(str);
		default:
			return NULL; // should never happen
	}
}

void jump_to_next_arg(int* arg, int* character)
{
	(*arg)++;
	*character = 0;
}

void set_error(t_argument* arg, t_errtype type, char name, void* value)
{
	arg->type = ARG_T_ERROR;
	arg->errtype = type;
	arg->name = name;
	arg->value = value;
}
