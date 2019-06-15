/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 17:18:20 by jwillem-          #+#    #+#             */
/*   Updated: 2019/06/14 23:28:42 by jwillem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_reg(t_all *all, int *k, char size)
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
	token = ft_newtokens(all, REGISTER, -1, size);
	token->str = ft_strsub(SPLIT, i, all->i - i);
	sep_char(all, k[0]);
	--k[0];
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
		return (vn_met(all, DIRLABEL, k, size));
	}
	++all->i;
	i = all->i;
	miniatoi(all);
	if (i - all->i == 0)
		return (0);
	token = ft_newtokens(all, DIRECT, -1, size);
	token->str = ft_strsub(SPLIT, i, all->i - i);
	sep_char(all, k[0]);
	--k[0];
	ft_tokenspush(&all->temp, token);
	return (1);
}

int		ft_idir(t_all *all, int *k, char size)
{
	unsigned i;
	t_tokens *token;

	quick_pass(all);
	if (SPLIT[all->i] == LABEL_CHAR)
		return (vn_met(all, INDIRLABEL, k, size));
	i = all->i;
	miniatoi(all);
	if (i - all->i == 0)
		return (0);
	token = ft_newtokens(all, INDIRECT, -1, size);
	token->str = ft_strsub(SPLIT, i, all->i - i);
	sep_char(all, k[0]);
	--k[0];
	ft_tokenspush(&all->temp, token);
	return (1);
}

void	get_argument(t_all *all, int *k, t_operation op, unsigned char arg)
{
	char	*v;
	int		f;

	f = 0;
	v = tablica(arg);
	quick_pass(all);
	v[0] == 1 ? f = ft_idir(all, k, IND_SIZE) : 0;
	!f && v[1] == 1 ? f = ft_dir(all, k, op) : 0;
	!f && v[2] == 1 ? f = ft_reg(all, k, T_REG) : 0;
	free(v);
	if (!f)
	{
		ft_error(all, Syntactic, Wrong_argument);
		while (SPLIT[all->i] && SPLIT[all->i] != ',' &&
			SPLIT[all->i] != ' ' && SPLIT[all->i] != '\t')
			++all->i;
	}
}

void	checkmet(t_all *all, t_type tp, char size, int *incorrect_lbl)
{
	unsigned		i;
	t_tokens		*token;
	int				f;

	f = tp == LABEL ? 0 : 1;
	i = all->i;
	if (f && SPLIT[all->i] != LABEL_CHAR)
		ft_error(all, Syntactic, No_colon_before);
	else if ((f && SPLIT[all->i] == LABEL_CHAR))
	{
		++all->i;
		i = all->i;
	}
	while (SPLIT[all->i] && SPLIT[all->i] != '\n')
	{
		if (!scan_met(all) && bad_lbl_char_manage(all, f, incorrect_lbl, i))
			break ;
		++all->i;
	}
	if (all->i > 0)
		f = !f && SPLIT[all->i - 1] == LABEL_CHAR ? all->i - i - 1 : all->i - i;
	token = ft_newtokens(all, tp, -1, size);
	token->str = ft_strsub(SPLIT, i, f);
	ft_tokenspush(&all->temp, token);
}
