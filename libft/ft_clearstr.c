/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clearstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 15:32:33 by mamartin          #+#    #+#             */
/*   Updated: 2022/09/17 22:51:42 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "utils.h"
#include "mandatory.h"

char	*ft_clearstr(char *str)
{
	char	*new;

	free(str);
	new = ft_calloc(1, 1);
	return (new);
}
