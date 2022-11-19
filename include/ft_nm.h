/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:39:12 by mamartin          #+#    #+#             */
/*   Updated: 2022/11/19 15:47:16 by kali             ###   ########.fr       */
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
	SUCCESS
}	t_ft_nm_error;

typedef struct
{
	void*		start;
	Elf64_Half	entry_size;
	Elf64_Half	entry_count;
}				t_shdr_table;

typedef struct
{
	t_shdr_table	shdrtab;
	void*			start;
	size_t 			size;
	bool			x64;
}					t_elf_file;

typedef struct
{
	void*		symbols;
	void*		names;
	Elf64_Xword	symcount;
	Elf64_Xword symsize;
}				t_symbol_table;

typedef struct			s_symbols
{
	Elf64_Addr			addr;
	Elf64_Word			name;
	unsigned char		type;
	unsigned char		binding;
	Elf64_Section		shndx;
	struct s_symbols*	next;
}						t_symbols;


t_symbols*  create_list(int symbols_count);
int     	list_size(t_symbols* symbols);
void    	print_list(t_symbols* symbols, t_symbol_table* symtab, t_elf_file bin);
void		load_list(t_symbol_table* symtab, t_symbols* symbols);
void 		ft_putnbr_hex(size_t nbr);
char 		detect_symbol_type(t_symbols* sym, const t_elf_file* binary);

#endif
