/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 15:46:13 by kali              #+#    #+#             */
/*   Updated: 2022/11/19 15:46:19 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sections.h"

char detect_symbol_type(t_symbols* sym, const t_elf_file* binary)
{
	if (sym->binding == STB_WEAK)
		return sym->addr ? 'W' : 'w';
	
	char type;
	if (sym->type == STT_FUNC)
		type = (sym->addr) ? 'T' : 'U';
	else if (sym->type == STT_OBJECT || sym->type == STT_NOTYPE)
	{
		Elf64_Shdr* section = load_section_by_index(binary, sym->shndx);
		if (!section)
			return '\0';

		if (section->sh_flags & SHF_WRITE)
		{
			if (section->sh_type == SHT_NOBITS)
				type = 'B';
			else if (
				section->sh_type == SHT_PROGBITS ||
				section->sh_type == SHT_DYNAMIC ||
				section->sh_type == SHT_INIT_ARRAY ||
				section->sh_type == SHT_FINI_ARRAY
			)	type = 'D';
			else
				return '?';
		}
		else
			type = 'R';
	}
	else
		return '?';
	return sym->binding == STB_GLOBAL ? type : type + 32;
}