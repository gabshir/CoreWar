/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 17:21:22 by jwillem-          #+#    #+#             */
/*   Updated: 2019/06/14 23:27:39 by jwillem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		scan_met(t_all *all)
{
	unsigned		j;

	j = 0;
	while (LABEL_CHARS[j])
	{
		if (SPLIT[all->i] != LABEL_CHARS[j])
			++j;
		else
			return (1);
	}
	return (0);
}

int		check_label_colon(t_all *all, unsigned i)
{
	unsigned	tmp_i;

	tmp_i = all->i;
	if (i > 0 && SPLIT[i - 1] == LABEL_CHAR)
		return (1);
	while (SPLIT[tmp_i])
	{
		if (SPLIT[tmp_i] == LABEL_CHAR)
			return (1);
		++tmp_i;
	}
	return (0);
}

void	sep_char(t_all *all, int k)
{
	if (k > 0)
	{
		quick_pass(all);
		SPLIT[all->i] != SEPARATOR_CHAR ?
		ft_error(all, Syntactic, No_comma) : ++all->i;
		quick_pass(all);
	}
}

int		vn_met(t_all *all, t_type tp, int *k, char size)
{
	int	incorrect_lbl;

	checkmet(all, tp, size, &incorrect_lbl);
	sep_char(all, k[0]);
	--k[0];
	return (1);
}

void	unknown_instr_error(t_all *all, int *size)
{
	ft_uniswap(&all->i, size, sizeof(int));
	ft_error(all, Syntactic, Unknown_instr);
	all->i = *size;
}
