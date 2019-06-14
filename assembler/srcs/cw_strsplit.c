/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 00:17:33 by jwillem-          #+#    #+#             */
/*   Updated: 2019/06/13 06:22:14 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static size_t	lines_quantity(char *champ)
{
	size_t	quantity;
	size_t	i;

	quantity = 0;
	i = -1;
	while (champ[++i])
		if (champ[i] == '\n')
			++quantity;
	if (champ[i - 1] != '\n')
		++quantity;
	return (quantity);
}

static char		*line_record(char *champ)
{
	static size_t	i;
	size_t			prev_i;
	char			*line;
	size_t			len;

	len = 0;
	prev_i = i - 1;
	while (champ && champ[i] != '\n')
	{
		++len;
		++i;
	}
	++len;
	SECURE_MALLOC(line = ft_strnew(len));
	line[--len] = '\n';
	while (++prev_i < i)
		line[len - (i - prev_i)] = champ[prev_i];
	++i;
	return (line);
}

char			**cw_strsplit(char *champ)
{
	char	**str;
	size_t	i;
	size_t	line_q;

	i = -1;
	if (!champ)
		return (NULL);
	line_q = lines_quantity(champ);
	SECURE_MALLOC(str = ft_memalloc(sizeof(char*) * (line_q + 1)));
	while (++i < line_q)
		str[i] = line_record(champ);
	return (str);
}
