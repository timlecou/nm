/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 17:04:03 by timlecou          #+#    #+#             */
/*   Updated: 2022/11/19 15:51:13 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <elf.h>
#include "ft_nm.h"
#include "libft.h"
#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

t_symbols*  create_list(int symbols_count)
{
    t_symbols*  sym = mmap(NULL, symbols_count * sizeof(sym), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

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

void	load_list(t_symbol_table* symtab, t_symbols* symbols)
{
	t_symbols*  tmp = symbols;
    Elf64_Sym*  syms = symtab->symbols;
    Elf64_Xword i = 0;

    while (i < symtab->symcount)
    {
        if (syms->st_name != 0 && ELF64_ST_TYPE(syms->st_info) != STT_FILE)
        {
            tmp->name = syms->st_name;
            tmp->addr = syms->st_value;
            tmp->type = ELF64_ST_TYPE(syms->st_info);
            tmp->binding = ELF64_ST_BIND(syms->st_info);
            tmp->shndx = syms->st_shndx;
            tmp = tmp->next;
        }
        syms = syms + 1;
        i++;
    }
    tmp->next = NULL;
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

void    print_zeros(size_t nbr)
{
    int     i = 1;
    while (nbr >= 16)
    {
        nbr /= 16;
        i++;
    }
    write(1, "0000000000000000", 16 - i);
}

void    print_list(t_symbols* symbols, t_symbol_table* symtab, t_elf_file bin)
{
    t_symbols*  tmp = symbols;
    char        type = 0;

    while (tmp->next)
    {
        if (tmp->addr != 0)
        {
            print_zeros(tmp->addr);
            ft_putnbr_hex(tmp->addr);
        }
        else
            write(1, "                ", 16);
        write(1, " ", 1);
        type = detect_symbol_type(tmp, &bin);
        write(1, &type, 1);
        write(1, " ", 1);
        ft_putendl_fd(symtab->names + tmp->name, 1);
        tmp = tmp->next;
    }
}