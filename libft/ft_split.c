/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <mamartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 00:28:47 by user42            #+#    #+#             */
/*   Updated: 2020/11/26 21:27:37 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory.h"

static int	count_words(char const *s, char sep)
{
	int	i;
	int	nb_words;

	i = 0;
	nb_words = 0;
	while (s[i] != '\0')
	{
		while (s[i] == sep)
			i++;
		while (s[i] != sep && s[i] != '\0')
			i++;
		nb_words++;
		if (s[i] == '\0' && s[i - 1] == sep)
			nb_words--;
	}
	return (nb_words);
}

static void	free_split(char **split, int k)
{
	while (k--)
		free(split[k]);
	free(split);
}

static char	**copy_strings(char **split, char const *s, char sep, int nb)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (k < nb)
	{
		while (s[i] == sep && s[i] != '\0')
			i++;
		while (s[i + j] != sep && s[i + j] != '\0')
			j++;
		split[k] = (char *)malloc(j + 1);
		if (!split[k])
		{
			free_split(split, k);
			return (NULL);
		}
		ft_strlcpy(split[k], s + i, j + 1);
		i += j;
		j = 0;
		k++;
	}
	return (split);
}

char		**ft_split(char const *s, char c)
{
	int		nb_words;
	char	**split;

	if (!s)
		return (NULL);
	nb_words = count_words(s, c);
	split = (char **)ft_calloc(nb_words + 1, sizeof(char *));
	if (!split)
		return (NULL);
	split = copy_strings(split, s, c, nb_words);
	split[nb_words] = NULL;
	return (split);
}
