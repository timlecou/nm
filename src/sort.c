/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 05:14:03 by mamartin          #+#    #+#             */
/*   Updated: 2022/12/05 09:55:58 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "libft.h"

static bool is_separator(char c)
{
	return (c == '_' || c == '.' || c == '@');
}

static int compare_symbols(const char* lname, const char* rname)
{
	int uppercase = 0;
	int separator = 0;
	int loff = 0;
	int roff = 0;

	while (lname[loff] && rname[roff])
	{
		char lc = ft_toupper(lname[loff]);
		char rc = ft_toupper(rname[roff]);

		if (is_separator(rc))
		{
			if (!separator && (!is_separator(lc) || (rc == '.' && lc == '_')))
				separator = 1;
			roff++;
		}
		if (is_separator(lc))
		{
			if (!separator && (!is_separator(rc) || (lc == '.' && rc == '_')))
				separator = -1;
			loff++;
		}
		if (!is_separator(rc) && !is_separator(lc))
		{
			char diff = lc - rc;
			if (diff)
				return diff;
			else if (ft_isalpha(lc) && ft_isalpha(rc))
			{
				int tmp = lname[loff] - rname[roff];
				if (!uppercase)
				{
					if (tmp == 32)
						uppercase = 1; // uppercase should go first
					else if (tmp == -32)
						uppercase = -1;
				}
			}

			roff++;
			loff++;
		}
	}

	if (lname[loff] != rname[roff])
		return lname[loff] ? lname[loff] : -rname[roff];
	else if (uppercase)
		return uppercase;
	return separator;
}

static void	swap_names(t_symbols* node_1, t_symbols* node_2)
{
    char*	tmp1 = node_1->name;
    node_1->name = node_2->name;
    node_2->name = tmp1;
}

static void	swap_addresses(t_symbols* node_1, t_symbols* node_2)
{
    Elf64_Addr	tmp1 = node_1->addr;
    node_1->addr = node_2->addr;
    node_2->addr = tmp1;
}

static void	swap_types(t_symbols* node_1, t_symbols* node_2)
{
    unsigned char	tmp1 = node_1->type;
    node_1->type = node_2->type;
    node_2->type = tmp1;
}

static void	swap_bindings(t_symbols* node_1, t_symbols* node_2)
{
    unsigned char	tmp1 = node_1->binding;
    node_1->binding = node_2->binding;
    node_2->binding = tmp1;
}

static void	swap_shndxs(t_symbols* node_1, t_symbols* node_2)
{
    Elf64_Section	tmp1 = node_1->shndx;
    node_1->shndx = node_2->shndx;
    node_2->shndx = tmp1;
}

void	sort_list(t_symbols* symbols, bool reverse)
{
	t_symbols*	tmp = symbols;
	t_symbols*	tmp_2 = symbols->next;
	bool		swap;
    int			ret;

    while (tmp->next)
    {
        tmp_2 = tmp->next;
        while (tmp_2->next)
        {
			ret = compare_symbols(tmp->name, tmp_2->name);
		    if (ret)
				swap = ((ret > 0) == !reverse);
			else
				swap = (tmp->addr > tmp_2->addr);

			if (swap)
            {
                swap_names(tmp, tmp_2);
                swap_addresses(tmp, tmp_2);
                swap_types(tmp, tmp_2);
                swap_bindings(tmp, tmp_2);
                swap_shndxs(tmp, tmp_2);
            }
            tmp_2 = tmp_2->next;
        }
        tmp = tmp->next;
    }
}
