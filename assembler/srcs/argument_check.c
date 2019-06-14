/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 17:18:20 by jwillem-          #+#    #+#             */
/*   Updated: 2019/06/14 17:20:11 by jwillem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			ft_reg(t_all *all, int *k, char size)
{
	int			s;
	unsigned	i;
	t_tokens	*token;

	quick_pass(all);
	if (SPLIT[all->i] != 'r')
		return (0);
	++all->i;
	i = all->i;
	s = miniatoi(all);
	if (all->i - i > 2 || i - all->i == 0 || s == 0)
		ft_error(all, Lexical, Incorrect_int);
	--k[0];
	token = ft_newtokens(all, REGISTER, -1, size);
	token->str = ft_strsub(SPLIT, i, all->i - i);
	sep_char(all, k[0]);
	ft_tokenspush(&all->temp, token);
	return (1);
}

int		ft_dir(t_all *all, int *k, t_operation op)
{
	unsigned	i;
	t_tokens	*token;
	char		size;

	quick_pass(all);
	size = op == zjmp || op == ldi || op == sti || op == ffork
			|| op == lldi || op == lfork ? 2 : 4;
	if (SPLIT[all->i] != DIRECT_CHAR)
		return (0);
	if (SPLIT[all->i + 1] == LABEL_CHAR)
	{
		++all->i;
		return (vn_met(all, DIRLABEL, k[0], size));
	}
	++all->i;
	i = all->i;
	miniatoi(all);
	if (i - all->i == 0)
		return (0);
	--k[0];
	token = ft_newtokens(all, DIRECT, -1, size);
	token->str = ft_strsub(SPLIT, i, all->i - i);
	sep_char(all, k[0]);
	ft_tokenspush(&all->temp, token);
	return (1);
}

int		ft_idir(t_all *all, int *k, char size)
{
	unsigned i;
	t_tokens *token;

	quick_pass(all);
	if (SPLIT[all->i] == LABEL_CHAR)
		return (vn_met(all, INDIRLABEL, k[0], size));
	i = all->i;
	miniatoi(all);
	if (i - all->i == 0)
		return (0);
	--k[0];
	token = ft_newtokens(all, INDIRECT, -1, size);
	token->str = ft_strsub(SPLIT, i, all->i - i);
	sep_char(all, k[0]);
	ft_tokenspush(&all->temp, token);
	return (1);
}
