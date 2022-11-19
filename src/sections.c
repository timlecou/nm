/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sections.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 07:36:02 by mamartin          #+#    #+#             */
/*   Updated: 2022/11/19 09:18:46 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_nm.h"

static bool validate_section_header(const t_elf_file* binary, void* ptr)
{
	/* Check that no offset could lead outside of the mapped content */
	if (binary->x64)
	{
		Elf64_Shdr* section = ptr;
		return (
			section->sh_link < binary->shdrtab.entry_count &&
			section->sh_offset + section->sh_size < binary->size &&
			section->sh_entsize <= section->sh_size
		);
	}
	else
	{
		Elf32_Shdr* section = ptr;
		return (
			section->sh_link < binary->shdrtab.entry_count &&
			section->sh_offset + section->sh_size < binary->size &&
			section->sh_entsize <= section->sh_size
		);		
	}
}

bool load_section_headers(t_elf_file* binary)
{
	Elf64_Ehdr* elfhdr = binary->start;
	t_shdr_table* shdrtab = &binary->shdrtab;
	Elf64_Off offset;

	binary->x64 =(elfhdr->e_ident[EI_CLASS] == ELFCLASS64);
	if (binary->x64)
	{
		offset = elfhdr->e_shoff;
		shdrtab->entry_size = elfhdr->e_shentsize;
		shdrtab->entry_count = elfhdr->e_shnum;
	}
	else
	{
		Elf32_Ehdr* elfhdr32 = (Elf32_Ehdr*)elfhdr;
		offset = elfhdr32->e_shoff;
		shdrtab->entry_size = elfhdr32->e_shentsize;
		shdrtab->entry_count = elfhdr32->e_shnum;
	}
	shdrtab->start = binary->start + offset;

	/* Make sure that the entire table is inside mapped memory  */
	return (binary->size <= offset + shdrtab->entry_count * shdrtab->entry_size);
}

Elf64_Shdr* load_section_by_index(const t_elf_file* binary, Elf64_Section idx)
{
	if (idx > binary->shdrtab.entry_count)
		return NULL;

	Elf64_Shdr* section = binary->shdrtab.start + idx * binary->shdrtab.entry_size;
	return validate_section_header(binary, section) ? section : NULL;
}

t_symbol_table* load_next_symtab(const t_elf_file* binary, t_symbol_table* symtab, bool* error)
{
	static Elf64_Section nextidx = 0;
	
	Elf64_Shdr* symhdr = binary->shdrtab.start + nextidx * binary->shdrtab.entry_size;
	Elf64_Section stridx;
	void* strtab;

	*error = false;
	while (nextidx++ < binary->shdrtab.entry_count && symhdr->sh_type != SHT_SYMTAB)
		symhdr = (void*)symhdr + binary->shdrtab.entry_size;

	if (nextidx > binary->shdrtab.entry_count)
		return NULL; // no more .symtab sections

	*error = (!validate_section_header(binary, symhdr));
	if (*error)
		return NULL; // incorrect offset

	/* Retrieve symbol table information */
	if (binary->x64)
	{
		symtab->symbols = binary->start + symhdr->sh_offset;
		symtab->symcount = symhdr->sh_size / symhdr->sh_entsize;
		symtab->symsize = symhdr->sh_entsize;
		stridx = symhdr->sh_link;
	}
	else
	{
		Elf32_Shdr* symhdr32 = (Elf32_Shdr *)symhdr;
		symtab->symbols = binary->start + symhdr32->sh_offset;
		symtab->symcount = symhdr32->sh_size / symhdr32->sh_entsize;
		symtab->symsize = symhdr32->sh_entsize;
		stridx = symhdr32->sh_link;
	}

	/* Retrieve symbol names in the .strtab section */
	strtab = load_section_by_index(binary, stridx);
	if (!strtab)
	{
		*error = true;
		return NULL;
	}

	if (binary->x64)
		symtab->names = binary->start + ((Elf64_Shdr*)strtab)->sh_offset;
	else
		symtab->names = binary->start + ((Elf32_Shdr*)strtab)->sh_offset;
	return symtab;
}