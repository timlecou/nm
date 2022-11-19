/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sections.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 07:39:31 by mamartin          #+#    #+#             */
/*   Updated: 2022/11/19 09:19:27 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _SECTIONS_H_
# define _SECTIONS_H_

# include "ft_nm.h"

bool load_section_headers(t_elf_file* binary);
Elf64_Shdr* load_section_by_index(const t_elf_file* binary, Elf64_Section idx);
t_symbol_table* load_next_symtab(const t_elf_file* binary, t_symbol_table* symtab, bool* error);

#endif