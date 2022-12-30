/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 17:04:03 by timlecou          #+#    #+#             */
/*   Updated: 2022/12/05 09:24:34 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "ft_nm.h"
#include "libft.h"

t_symbols*  create_list(int symbols_count)
{
    t_symbols*  sym = mmap(NULL, symbols_count * sizeof(t_symbols), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (sym == MAP_FAILED)
		return NULL;

    int i = 0;
    t_symbols*  tmp = sym;
    while (i < symbols_count)
    {
        tmp->next = tmp + 1;
        i++;
        tmp = tmp->next;
    }
    tmp->next = NULL;
    return (sym);
}

int     list_size(t_symbols* symbols)
{
    int i = 0;
    t_symbols*  tmp = symbols;

    while (tmp->next)
    {
        tmp = tmp->next;
        i++;
    }
    return (i);
}

static bool validate_symbol(t_symbols* symbols, t_options* params)
{
	if (params->show_all || (symbols->strndx && symbols->type != STT_FILE))
    {
		if (params->undefined_only)
			return (!symbols->addr);
		else if (params->extern_only)
			return (symbols->binding != STB_LOCAL);
		return true;
    }
	return false;
}

bool	load_list(t_sections* s, t_options* params, t_symbols* symbols, t_elf_file* bin)
{
	void* 		sym = s->symtab->data.buffer + s->symtab->data.entsize;
	t_symbols*  tmp = symbols;
    Elf64_Xword i = 1;

	while (i < s->symtab->data.entcount)
    {
		if (bin->x64)
        {
			Elf64_Sym* sym64 = sym;
			tmp->addr = sym64->st_value;
			tmp->type = ELF64_ST_TYPE(sym64->st_info);
			tmp->binding = ELF64_ST_BIND(sym64->st_info);
			tmp->visibility = ELF64_ST_VISIBILITY(sym64->st_other);
			tmp->shndx = sym64->st_shndx;
			tmp->strndx = sym64->st_name;
		}
		else
		{
			Elf32_Sym *sym32 = sym;
			tmp->addr = sym32->st_value;
			tmp->type = ELF32_ST_TYPE(sym32->st_info);
			tmp->binding = ELF32_ST_BIND(sym32->st_info);
			tmp->visibility = ELF32_ST_VISIBILITY(sym32->st_other);
			tmp->shndx = sym32->st_shndx;
			tmp->strndx = sym32->st_name;
		}

		if (validate_symbol(tmp, params))
		{
			bool success = true;
			if (tmp->strndx)
				success = load_name(&tmp->name, s->strtab, tmp->strndx);
			else if (tmp->type == STT_SECTION)
				success = load_name(&tmp->name, s->shstrtab, s->headers[tmp->shndx].strndx);
			else
				tmp->name = "";
			if (!success)
				return false;

			tmp = tmp->next;
		}

		sym = sym + s->symtab->data.entsize;
        i++;
    }
    tmp->next = NULL;
	return true;
}

void ft_putnbr_hex(size_t nbr)
{
    const char* digits = "0123456789abcdef";

    if (nbr >= 16)
    {
        ft_putnbr_hex(nbr / 16);
        ft_putchar_fd(digits[nbr % 16], 1);
    }
    else
        ft_putchar_fd(digits[nbr % 16], 1);
}

void    print_zeros(size_t nbr, short arch)
{
    int     i = 1;
    while (nbr >= 16)
    {
        nbr /= 16;
        i++;
    }
    write(1, "0000000000000000", arch - i);
}

bool    print_list(t_symbols* symbols, t_sections* sections, t_elf_file* bin)
{
    t_symbols*  tmp = symbols;
    char        type = 0;

    while (tmp->next)
    {
		type = detect_symbol_type(tmp, sections);
		if (!type)
			return false;

		if (tmp->addr != 0)
		{
			print_zeros(tmp->addr, (bin->x64 ? 16 : 8));
			ft_putnbr_hex(tmp->addr);
		}
		else
		{
			if (ft_toupper(type) != 'W' && ft_toupper(type) != 'U')
				write(1, "0000000000000000", (bin->x64 + 1) * 8);
			else
				write(1, "                ", (bin->x64 + 1) * 8);
		}
		write(1, " ", 1);
		write(1, &type, 1);
		write(1, " ", 1);
		ft_putendl(tmp->name);
        tmp = tmp->next;
    }
	return true;
}
