/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 17:08:47 by mamartin          #+#    #+#             */
/*   Updated: 2022/12/03 18:58:57 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "libft.h"

# define N_OPTIONS_SUPPORTED 7

static void print_option_usage(char optname, const char* desc)
{
	ft_putstr(" -");
	ft_putchar(optname);
	ft_putstr(",\t");
	ft_putendl(desc);
}

void print_usage(const char* progname)
{
	ft_putstr("Usage: ");
	ft_putstr(progname);
	ft_putstr(" [option(s)] [file(s)]\n List symbols in [file(s)] (a.out by default).\n The options are:\n");

	print_option_usage('a', "Display all symbols");
	print_option_usage('g', "Display only external symbols");
	print_option_usage('p', "Do not sort the symbols");
	print_option_usage('r', "Reverse the sense of the sort");
	print_option_usage('u', "Display only undefined symbols");
	print_option_usage('D', "Display the dynamic symbols rather than the normal symbols");
	print_option_usage('h', "Display this information");
	exit(EXIT_SUCCESS);
}

t_ft_nm_error parse_options(int argc, char** argv, t_options* opt)
{
	static t_expected_opts VALID_OPTIONS[] = {
		{ .name = 'p', .has_param = false },
		{ .name = 'r', .has_param = false },
		{ .name = 'a', .has_param = false },
		{ .name = 'g', .has_param = false },
		{ .name = 'u', .has_param = false },
		{ .name = 'D', .has_param = false },
		{ .name = 'h', .has_param = false },
	};

	opt->filenames = ft_calloc(argc, sizeof(const char*));
	if (!opt->filenames)
		return OOM;

	t_argument arg;
	int ret;
	while ((ret = ft_getarg(argc, argv, VALID_OPTIONS, N_OPTIONS_SUPPORTED, &arg)) == 0)
	{
		switch (arg.type)
		{
			case ARG_T_OPTION:
				switch (arg.name)
				{
					case 'p':
						opt->sort = SYMSORT_DISABLED;
						break;
					case 'r':
						if (opt->sort != SYMSORT_DISABLED)
							opt->sort = SYMSORT_REVERSE;
						break;
					case 'a':
						opt->show_all = true;
						break;
					case 'g':
						opt->extern_only = true;
						break;
					case 'u':
						opt->undefined_only = true;
						break;
					case 'D':
						opt->dynamic_only = true;
						break;
					case 'h':
						free(opt->filenames);
						print_usage(*argv);
						break;
					default: // should never happen
						break;
				}
				break ;
			case ARG_T_PARAMETER:
				opt->filenames[opt->fcount] = (char*)arg.value;
				opt->fcount++;
				break ;
			case ARG_T_ERROR:
				free(opt->filenames);
				ft_putstr_fd(*argv, STDERR_FILENO);
				ft_putstr_fd(": invalid option -- \'", STDERR_FILENO);
				ft_putchar_fd(arg.name, STDERR_FILENO);
				ft_putstr_fd("\'\n", STDERR_FILENO);
				print_usage(*argv);
		}
	}

	if (opt->undefined_only)
		opt->show_all = false;
	return SUCCESS;
}
