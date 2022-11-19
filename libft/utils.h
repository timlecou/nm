/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 22:40:12 by mamartin          #+#    #+#             */
/*   Updated: 2022/09/17 22:47:09 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _UTILS_H_
#define _UTILS_H_

/*
**	SOME USEFUL FUNCTIONS
**
**	ft_itoa_base	-> like itoa but with a given numeral system
**	get_next_line	-> read a line from a file descriptor
**	ft_free_map		-> free any given 2D array ending with a NULL element
**	ft_clearstr		-> free the string pointed by str and replace it by a new
**						empty string
*/

char	*ft_itoa_base(unsigned long long nbr, char *base);
int		get_next_line(int fd, char **line);
void	ft_free_map(char **map);
char	*ft_clearstr(char *str);

#endif
