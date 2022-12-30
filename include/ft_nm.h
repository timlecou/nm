/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:39:12 by mamartin          #+#    #+#             */
/*   Updated: 2022/12/03 18:33:18 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _NM_H_
# define _NM_H_

# include <stddef.h>
# include <stdbool.h>
# include <stdlib.h>
# include <elf.h>

typedef enum
{
	FILE_MAP_FAIL,
	BAD_FILE_FORMAT,
	NO_SYMBOLS,
	OOM,
	OUT_OF_BOUNDS,
	BAD_OPTION,
	SUCCESS
}	t_ft_nm_error;

typedef struct
{
	char*			name;
	Elf64_Word		strndx;
	Elf64_Word		type;
	Elf64_Xword		flags;
	Elf64_Word		link;
	struct 
	{
		void*		buffer;
		Elf64_Xword size;
		Elf64_Xword entsize;
		Elf64_Xword entcount;
	} 				data;
}	t_shdr;

typedef struct
{
	t_shdr*			headers;
	t_shdr*			symtab;
	t_shdr*			strtab;
	t_shdr*			shstrtab;
	Elf64_Section	count;
}				t_sections;

typedef struct
{
	void*			buffer;
	size_t			size;
	Elf64_Section	nsections;
	bool			x64;
}					t_elf_file;

typedef struct s_symbols
{
	char*				name;
	Elf64_Word			strndx;
	Elf64_Addr			addr;
	unsigned char		type;
	unsigned char		binding;
	unsigned char		visibility;
	Elf64_Section		shndx;
	struct s_symbols*	next;
}						t_symbols;

typedef enum
{
	SYMSORT_DEFAULT,
	SYMSORT_REVERSE,
	SYMSORT_DISABLED
}	t_symsort;

typedef struct
{
	const char**	filenames;
	int				fcount;

	t_symsort		sort;
	bool			show_all;
	bool			extern_only;
	bool			undefined_only;
	bool			dynamic_only;
}					t_options;

/* sections management */
t_ft_nm_error	load_sections(t_elf_file* bin, t_sections* s, bool dynamic);
bool			load_name(char** dest, t_shdr* strtab, Elf64_Word strndx);

/* List helpers */
t_symbols*	create_list(int symbols_count);
int			list_size(t_symbols* symbols);
bool		print_list(t_symbols* symbols, t_sections* sections, t_elf_file* bin);
bool		load_list(t_sections* s, t_options* params, t_symbols* symbols, t_elf_file* bin);
void		sort_list(t_symbols* symbols, bool reverse);
void		ft_putnbr_hex(size_t nbr);
char		detect_symbol_type(t_symbols* sym, t_sections* sections);

/* Program options parsing */
t_ft_nm_error parse_options(int argc, char** argv, t_options* opt);

#endif
