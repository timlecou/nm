/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sections.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 07:36:02 by mamartin          #+#    #+#             */
/*   Updated: 2022/12/05 17:42:40 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#include "ft_nm.h"
#include "libft.h"

static bool load_section_info(t_shdr* dest, void* src, t_elf_file* bin)
{
	if (bin->x64)
	{
		dest->strndx = ((Elf64_Shdr*)src)->sh_name;
		dest->type = ((Elf64_Shdr*)src)->sh_type;
		dest->flags = ((Elf64_Shdr*)src)->sh_flags;
		dest->link = ((Elf64_Shdr*)src)->sh_link;
		dest->data.buffer = bin->buffer + ((Elf64_Shdr*)src)->sh_offset;
		dest->data.size = ((Elf64_Shdr*)src)->sh_size;
		dest->data.entsize = ((Elf64_Shdr*)src)->sh_entsize;
	}
	else
	{
		dest->strndx = ((Elf32_Shdr*)src)->sh_name;
		dest->type = ((Elf32_Shdr*)src)->sh_type;
		dest->flags = ((Elf32_Shdr*)src)->sh_flags;
		dest->link = ((Elf32_Shdr*)src)->sh_link;
		dest->data.buffer = bin->buffer + ((Elf32_Shdr*)src)->sh_offset;
		dest->data.size = ((Elf32_Shdr*)src)->sh_size;
		dest->data.entsize = ((Elf32_Shdr*)src)->sh_entsize;		
	}

	if (dest->data.entsize)
		dest->data.entcount = dest->data.size / dest->data.entsize;

	/* Check that each pointer stays inside mapped content */
	return (
		dest->link < bin->nsections &&
		(dest->data.buffer + dest->data.size <= bin->buffer + bin->size || (dest->type != SHT_SYMTAB && dest->type != SHT_STRTAB)) &&
		dest->data.entsize <= dest->data.size
	);
}

bool load_name(char** dest, t_shdr* strtab, Elf64_Word strndx)
{
	char* strname = strtab->data.buffer;
	Elf64_Xword i = strndx;
	while (i < strtab->data.size && strname[i])
		i++;

	*dest = strtab->data.buffer + strndx;
	return !(i == strtab->data.size); // check string is null-terminated
}

t_ft_nm_error	load_sections(t_elf_file* bin, t_sections* s, bool dynamic)
{
	void* shdrs;
	Elf64_Off shoff;
	Elf64_Half entsize;
	Elf64_Half shstrndx;

	if (bin->x64)
	{
		bin->nsections = ((Elf64_Ehdr*)bin->buffer)->e_shnum;
		shoff = ((Elf64_Ehdr*)bin->buffer)->e_shoff;
		entsize = ((Elf64_Ehdr*)bin->buffer)->e_shentsize;
		shstrndx = ((Elf64_Ehdr*)bin->buffer)->e_shstrndx;
	}
	else
	{
		bin->nsections = ((Elf32_Ehdr*)bin->buffer)->e_shnum;
		shoff = ((Elf32_Ehdr*)bin->buffer)->e_shoff;
		entsize = ((Elf32_Ehdr*)bin->buffer)->e_shentsize;
		shstrndx = ((Elf32_Ehdr*)bin->buffer)->e_shstrndx;
	}

	if (shoff + bin->nsections * entsize > bin->size)
		return OUT_OF_BOUNDS;

	shdrs = bin->buffer + shoff;

	s->headers = ft_calloc(bin->nsections, sizeof(t_shdr));
	if (!s->headers)
		return OOM;

	int i = 0;
	s->shstrtab = s->headers + shstrndx;
	if (load_section_info(s->shstrtab, shdrs + shstrndx * entsize, bin))
	{
		void *curhdr = shdrs;
		Elf64_Word symtype = (dynamic) ? SHT_DYNSYM : SHT_SYMTAB;
		while (i < bin->nsections)
		{
			if (i != shstrndx)
			{
				if (!load_section_info(s->headers + i, curhdr, bin))
					break ;

				if (s->headers[i].type == symtype)
				{
					s->symtab = s->headers + i;
					s->strtab = s->headers + s->headers[i].link;
				}
			}

			if (!load_name(&s->headers[i].name, s->shstrtab, s->headers[i].strndx))
				break ;

			curhdr += entsize;
			i++;
		}
	}

	if (i != bin->nsections)
	{
		free(s->headers);
		return OUT_OF_BOUNDS;
	}
	else if (!s->symtab)
	{
		free(s->headers);
		return NO_SYMBOLS;
	}

	s->count = bin->nsections;
	return SUCCESS;
}
