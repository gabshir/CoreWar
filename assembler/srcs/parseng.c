/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseng.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:48:58 by gabshire          #+#    #+#             */
/*   Updated: 2019/06/15 02:59:55 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		bad_lbl_char_manage(t_all *all, int f, int *incorrect_lbl, int i)
{
	if (!f && SPLIT[all->i] == LABEL_CHAR)
		++all->i;
	else if ((SPLIT[all->i] == SEPARATOR_CHAR
		|| SPLIT[all->i] == ALT_COMMENT_CHAR
		|| SPLIT[all->i] == COMMENT_CHAR || SPLIT[all->i] == '\n'
		|| SPLIT[all->i] == '\t' || SPLIT[all->i] == ' ') && f)
		return (1);
	else if ((*incorrect_lbl = check_label_colon(all, i)))
	{
		ft_error(all, Lexical, Wrong_lchar);
		while (SPLIT[all->i] && SPLIT[all->i] != ',' &&
			SPLIT[all->i] != ' ' && SPLIT[all->i] != '\t')
			++all->i;
	}
	return (1);
}

void	ft_parseng(t_all *all, t_op a, t_operation op)
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

int		instr_not_found(t_all *all, int *i, int *incorrect_lbl, t_op *a)
{
	checkmet(all, LABEL, 0, incorrect_lbl);
	(*i) = -1;
	quick_pass(all);
	if (!SPLIT[all->i] || SPLIT[all->i] == '\n')
	{
		ft_lstpush(&all->parsing, ft_lstnew_ptr(all->temp));
		all->temp = NULL;
		return (0);
	}
	(*a) = operations(all, i);
	return (1);
}

void	tokens(t_all *all)
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
		size = all->i;
		if (!instr_not_found(all, &i, &incorrect_lbl, &a))
			return ;
	}
	if (!a.cmd[0] && !incorrect_lbl)
		unknown_instr_error(all, &size);
	size = i == live || i == zjmp || i == ffork
			|| i == lfork ? 1 : 2;
	token = ft_newtokens(all, INSTRUCTION, i, (char)size);
	token->str = ft_strsub((char *)a.cmd, 0, ft_strlen((char *)a.cmd));
	ft_tokenspush(&all->temp, token);
	a.cmd[0] ? ft_parseng(all, a, i) : 0;
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
