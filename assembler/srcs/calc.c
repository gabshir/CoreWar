/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabshire <gabshire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 00:29:36 by gabshire          #+#    #+#             */
/*   Updated: 2019/06/08 03:57:38 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*byte_numbers(int c)
{
	int		k;
	char	*str;
	char	l;

	c < 0 ? c = ~c : 0;
	k = kol_sim(c, 16);
	if (!(str = (char *)ft_memalloc(sizeof(char) * k + 1)))
		return (NULL);
	while (c)
	{
		l = c % 16;
		str[--k] = l > 9 ? c - 10 + 'a' : c + '0';
		c /= 10;
	}
	return (str);
}

char	*byte_string(char *s)
{
	char	*str;
	int 	i;

	str = ft_strnew(0);
	i = 0;
	while (s[i])
	{
		str = ft_strjoin_free(str, byte_numbers(s[i]), 3);
		++i;
	}
	return (str);
}

