/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseng.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:48:58 by gabshire          #+#    #+#             */
/*   Updated: 2019/06/14 20:24:16 by jwillem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		checkmet(t_all *all, t_type tp, char size, int *incorrect_lbl)
{
	unsigned		j;
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
		j = scan_met(all);
		if (!j)
		{
			if (!f && SPLIT[all->i] == LABEL_CHAR)
				++all->i;
			else if ((SPLIT[all->i] == SEPARATOR_CHAR
			|| SPLIT[all->i] == ALT_COMMENT_CHAR
			|| SPLIT[all->i] == COMMENT_CHAR || SPLIT[all->i] == '\n'
			|| SPLIT[all->i] == '\t' || SPLIT[all->i] == ' ') && f)
				break ;
			else if ((*incorrect_lbl = check_label_colon(all, i)))
			{
				ft_error(all, Lexical, Wrong_lchar);
				while (SPLIT[all->i] && SPLIT[all->i] != ',' &&
					SPLIT[all->i] != ' ' && SPLIT[all->i] != '\t')
					++all->i;
			}
			break ;
		}
		++all->i;
	}
	if (all->i > 0)
		f = !f && SPLIT[all->i - 1] == LABEL_CHAR ? all->i - i - 1 : all->i - i;
	token = ft_newtokens(all, tp, -1, size);
	token->str = ft_strsub(SPLIT, i, f);
	ft_tokenspush(&all->temp, token);
}

void		get_argument(t_all *all, int *k, t_operation op, unsigned char arg)
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

void		ft_parseng(t_all *all, t_op a, t_operation op)
{
	unsigned	j;
	int			k;

	j = 0;
	k = a.arg_q - 1;
	all->i += ft_strlen((char *)a.cmd);
	while (j < 3)
	{
		SPLIT[all->i] == SEPARATOR_CHAR ? ++all->i : 0;
		if (a.arg_type[j])
			get_argument(all, &k, op, a.arg_type[j]);
		++j;
	}
	last_check(all) ? ft_error(all, Syntactic, Odd_argument) : 0;
}

void			tokens(t_all *all)
{
	t_op		a;
	t_tokens	*token;
	int			i;
	int			size;
	int			incorrect_lbl;

	quick_pass(all);
	i = -1;
	a = operations(all, &i);
	if (!a.cmd[0])
	{
		checkmet(all, LABEL, 0, &incorrect_lbl);
		i = -1;
		quick_pass(all);
		if (!SPLIT[all->i] || SPLIT[all->i] == '\n')
		{
			ft_lstpush(&all->parsing, ft_lstnew_ptr(all->temp));
			all->temp = NULL;
			return ;
		}
		size = all->i;
		a = operations(all, &i);
	}
	if (!a.cmd[0] && !incorrect_lbl)
	{
		ft_uniswap(&all->i, &size, sizeof(int));
		ft_error(all, Syntactic, Unknown_instr);
		all->i = size;
	}
	size = i == live || i == zjmp || i == ffork
			|| i == lfork || i == aff ? 1 : 2;
	token = ft_newtokens(all, INSTRUCTION, i, (char)size);
	token->str = ft_strsub((char *)a.cmd, 0, ft_strlen((char *)a.cmd));
	ft_tokenspush(&all->temp, token);
	if (a.cmd[0])
		ft_parseng(all, a, i);
}

void	parseng(t_all *all)
{
	size_t	last_line_len;

	while (checkform(all))
	{
		if (SPLIT)
		{
			quick_pass(all);
			tokens(all);
			all->temp ? ft_lstpush(&all->parsing, ft_lstnew_ptr(all->temp)) : 0;
			all->temp = NULL;
		}
	}
	last_line_len = ft_strlen(SPLIT);
	if (SPLIT[last_line_len - 1] != '\n')
	{
		all->i = last_line_len - 1;
		ft_error(all, Syntactic, No_last_line);
	}
}
