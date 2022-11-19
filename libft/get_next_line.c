/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 15:18:27 by mamartin          #+#    #+#             */
/*   Updated: 2022/09/17 22:51:16 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "mandatory.h"
#include "utils.h"

#define BUFFER_SIZE 1024

static int		copy_buf(char **tmp, char *buf)
{
	char	*save;
	int		index;
	int		i;

	index = 0;
	save = *tmp;
	i = ft_strlen(save);
	while (buf[index] != '\n' && buf[index])
		index++;
	*tmp = (char *)malloc(ft_strlen(*tmp) + index + 1);
	if (!(*tmp))
		return (0);
	if (save)
	{
		ft_strlcpy(*tmp, save, i + 1);
		free(save);
	}
	ft_strlcpy(*tmp + i, buf, index + 1);
	return (1);
}

static int		copy_line(char **line, char **tmp)
{
	if (*tmp)
	{
		*line = ft_strdup(*tmp);
		if (*line == NULL)
			return (-1);
		free(*tmp);
		*tmp = NULL;
	}
	else
	{
		*line = (char *)malloc(1);
		if (*line == NULL)
			return (-1);
		(*line)[0] = '\0';
	}
	return (0);
}

static int		search_newline(char **line, char *buf, char **tmp)
{
	int	index;

	index = 0;
	while (buf[index] != '\n' && buf[index])
		index++;
	if (buf[index] == '\0')
		return (0);
	copy_line(line, tmp);
	if (index < BUFFER_SIZE - 1)
		*tmp = ft_strdup(buf + index + 1);
	return (1);
}

static int		check_tmp(char *tmp, char **line)
{
	int		i;

	i = 0;
	if (!tmp)
		return (0);
	while (tmp[i] != '\n' && tmp[i])
		i++;
	if (tmp[i] != '\n')
		return (0);
	*line = (char *)malloc(i + 1);
	if (!(*line))
		return (-1);
	ft_strlcpy(*line, tmp, i + 1);
	ft_strlcpy(tmp, tmp + i + 1, ft_strlen(tmp) - i);
	return (1);
}

int				get_next_line(int fd, char **line)
{
	static char	*tmp = NULL;
	char		buf[BUFFER_SIZE + 1];
	int			ret;

	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (-1);
	if ((ret = check_tmp(tmp, line)) != 0)
		return (ret);
	while ((ret = read(fd, buf, BUFFER_SIZE)))
	{
		if (ret == -1)
			return (-1);
		buf[ret] = '\0';
		if (!copy_buf(&tmp, buf))
			return (-1);
		if (search_newline(line, buf, &tmp))
		{
			if (!line)
				return (-1);
			return (1);
		}
	}
	return (copy_line(line, &tmp));
}
