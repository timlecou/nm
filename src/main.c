/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:38:42 by mamartin          #+#    #+#             */
/*   Updated: 2022/12/25 21:00:11 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#include "ft_nm.h"
#include "libft.h"

static void* map_file_content(const char* filename, size_t* size)
{
	int fd = open(filename, O_RDONLY);
	if (fd == -1)
		return MAP_FAILED;

	struct stat info;
	if (fstat(fd, &info) == -1)
	{
		close(fd);
		return MAP_FAILED;
	}
	
	void* mapped = mmap(NULL, info.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	
	close(fd);
	*size = info.st_size;
	return mapped;
}

static int fatal(t_ft_nm_error code, const char* prefix)
{
	static const char* errmsgs[] = {
		"failed to map file in memory",
		"file format not recognized",
		"no symbols",
		"out of memory",
		"pointer outside of mapped content"
	};

	ft_putstr_fd(prefix, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(errmsgs[code], STDERR_FILENO);
	return EXIT_FAILURE;
}

static bool detect_format(t_elf_file* bin)
{
	Elf64_Ehdr* elfhdr = bin->buffer;
	switch (elfhdr->e_ident[EI_CLASS])
	{
		case ELFCLASS32:
			bin->x64 = false;
			break;
		case ELFCLASS64:
			bin->x64 = true;
			break;
		default:
			return false;
	}

	return (
		ft_memcmp(ELFMAG, elfhdr->e_ident, 4) == 0 &&
		(elfhdr->e_ident[EI_CLASS] == ELFCLASS32 || elfhdr->e_ident[EI_CLASS] == ELFCLASS64) &&
		(elfhdr->e_ident[EI_DATA] == ELFDATA2LSB || elfhdr->e_ident[EI_DATA] == ELFDATA2MSB) &&
		elfhdr->e_ident[EI_VERSION] == EV_CURRENT &&
		elfhdr->e_type != ET_CORE &&
		(elfhdr->e_machine == EM_386 || elfhdr->e_machine == EM_X86_64)
	);
}

int main(int argc, char** argv)
{
	t_options params = {0};
	if (argc == 1)
	{
		params.filenames = malloc(sizeof(const char*));
		if (!params.filenames)
			return fatal(OOM, *argv);
	}
	else
	{
		if (parse_options(argc, argv, &params) == OOM)
			return fatal(OOM, *argv);
	}

	if (params.fcount == 0)
	{
		*params.filenames = "a.out";
		params.fcount = 1;
	}

	int i;
	for (i = 0; i < params.fcount; i++)
	{
		const char* fname = params.filenames[i];
		if (params.fcount != 1)
		{
			ft_putchar('\n');
			ft_putstr(fname);
			ft_putstr(":\n");
		}

		t_elf_file bin = {0};
		bin.buffer = map_file_content(fname, &bin.size);
		if (bin.buffer == MAP_FAILED)
		{
			fatal(FILE_MAP_FAIL, fname);
			continue ;
		}

		if (!detect_format(&bin))
		{
			munmap(bin.buffer, bin.size);
			fatal(BAD_FILE_FORMAT, fname);
			continue ;
		}

		t_sections sections = {0};
		t_ft_nm_error status = load_sections(&bin, &sections, params.dynamic_only);
		if (status != SUCCESS)
		{
			munmap(bin.buffer, bin.size);
			fatal(status, fname);
			continue ;
		}

		t_symbols *symbols = create_list(sections.symtab->data.entcount);
		if (!symbols)
		{
			free(sections.headers);
			munmap(bin.buffer, bin.size);
			fatal(OOM, fname);			
			continue ;
		}

		if (!load_list(&sections, &params, symbols, &bin))
		{
			munmap(symbols, sections.symtab->data.entcount * sizeof(t_symbols));
			munmap(bin.buffer, bin.size);
			free(sections.headers);
			fatal(OUT_OF_BOUNDS, fname);
			continue ;
		}

		if (params.sort != SYMSORT_DISABLED)
			sort_list(symbols, (params.sort == SYMSORT_REVERSE));
		bool ret = print_list(symbols, &sections, &bin);

		munmap(symbols, sections.symtab->data.entcount * sizeof(t_symbols));
		munmap(bin.buffer, bin.size);
		free(sections.headers);

		if (!ret)
		{
			fatal(OUT_OF_BOUNDS, fname);
			continue ;
		}
	}

	free(params.filenames);
	return EXIT_SUCCESS;
}
