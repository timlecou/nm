/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 18:39:50 by mamartin          #+#    #+#             */
/*   Updated: 2020/11/28 14:52:34 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory.h"

static int		ft_ischarset(char c, char const *charset)
{
	int	i;

	i = 0;
	while (charset[i] != '\0')
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	ft_strlen_nocharset(char const *s, char const *charset)
{
	size_t	i_start;
	size_t	i_end;

	i_start = 0;
	i_end = ft_strlen(s) - 1;
	while (ft_ischarset(s[i_start], charset))
		i_start++;
	while (ft_ischarset(s[i_end], charset) && i_end)
		i_end--;
	if (i_start == ft_strlen(s))
		return (0);
	else
		return (i_end - i_start + 1);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	size_t	length;
	char	*trim;
	int		i;

	i = 0;
	if (!s1)
		return (NULL);
	length = ft_strlen_nocharset(s1, set);
	trim = (char *)malloc(length + 1);
	if (!trim)
		return (NULL);
	while (ft_ischarset(*s1, set))
		s1++;
	while (length--)
	{
		trim[i] = *s1;
		i++;
		s1++;
	}
	trim[i] = '\0';
	return (trim);
}
