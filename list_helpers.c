/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 17:04:03 by timlecou          #+#    #+#             */
/*   Updated: 2022/11/18 19:22:43 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <elf.h>
#include "ft_nm.h"
#include "libft.h"
#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>

static const char* types[] = {
	"STT_NOTYPE",
	"STT_OBJECT",
	"STT_FUNC",
	"STT_SECTION",
	"STT_FILE",
	"STT_COMMON",
	"STT_TLS",
	"STT_NUM",
	"STT_LOOS",
	"STT_GNU_IFUNC",
	"STT_HIOS",
	"STT_LOPROC",
	"STT_HIPROC"
};

static const char* bindings[] = {
	"STB_LOCAL",
	"STB_GLOBAL",
	"STB_WEAK",
	"STB_NUM"
};

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

void    print_list(t_symbols* symbols)
{
    t_symbols*  tmp = symbols;

    ft_putstr_fd("ADDRESS", 1);
    write(1, "\t\t", 2);
    ft_putstr_fd("TYPE", 1);
    write(1, "\t\t\t", 3);
    ft_putstr_fd("BINDING", 1);
    write(1, "\t\t\t", 3);
    ft_putendl_fd("NAME", 1);
    write(1, "\n", 1);
    while (tmp->next)
    {
        ft_putnbr_hex(tmp->addr);
        write(1, "\t\t", 2);
        ft_putstr_fd(types[tmp->type], 1);
        write(1, "\t\t", 2);
        ft_putstr_fd(bindings[tmp->binding], 1);
        write(1, "\t\t", 2);
        ft_putendl_fd(tmp->name, 1);
        tmp = tmp->next;
    }
}
