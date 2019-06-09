/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseng.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:48:58 by gabshire          #+#    #+#             */
/*   Updated: 2019/06/09 20:36:25 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*tablica(int c)
{
	int		i;
	char	*str;

	str = ft_memalloc(4);
	i = 3;
	while(c)
	{
		str[--i] = c % 2;
		c /= 2;
	}
	return (str);
}

int		miniatoi(t_all *all)
{
	unsigned	i;
	int 		s;
	int 		f;
	int 		l;

	s = 0;
	l = 0;
	i = all->i;
	f = all->line[i] == '-' ? 1 : 0;
	f ? ++i : 0;
	while(all->line[i] && all->line[i] >= '0' && all->line[i] <= '9')
	{
		s = s * 10 + all->line[i] - '0';
		++i;
		l = 1;
	}
	!l && f ? ft_error(all, Lexical, Incorrect_int) : 0;
	all->i = i;
	return (s);
}

int scan_met(t_all *all)
{
	unsigned		j;

	j = 0;
	while(LABEL_CHARS[j])
	{
		if (all->line[all->i] != LABEL_CHARS[j])
			++j;
		else
			return (1);
	}
	return (0);
}

void    checkmet(t_all *all, t_type	tp)
{
	unsigned		j;
	unsigned 		i;
	t_tokens		*token;
	int 			f;

	f = tp == LABEL ? 0 : 1; //если не метка то f == 1
	i = all->i;
	f && all->line[all->i] != LABEL_CHAR ? ft_error(all, Syntactic, No_colon_before) : ++all->i; // если не метка то должна начинаться с :
	while(all->line[all->i])
	{
		j = scan_met(all); //j == 0 запрщенный символ
		!j && all->line[all->i] != LABEL_CHAR  && !f ? ft_error(all, Lexical, Wrong_lchar) : 0; // метка но в конце нет :
		if (!j && !f && all->line[all->i] == LABEL_CHAR)
		{
			++all->i;
			break;
		}
		if (!j && all->line[all->i] == SEPARATOR_CHAR && f)
			break;
		if (!j)
			break;
		++all->i;
	}
	token = ft_newtokens(all, tp, -1);
	token->str = ft_strsub(all->line, i, all->i - i);
	ft_tokenspush(&all->temp, token);
}

int 	ft_reg(t_all *all, int *k)
{
	int			s;
	unsigned	i;
	t_tokens	*token;

	quick_pass(all);
	if (all->line[all->i] != 'r')
		return (0);
	++all->i;
	i = all->i;
	s = miniatoi(all);
	if (all->i - i > 2 || i - all->i == 0 || s == 0)
		ft_error(all, Lexical, Incorrect_int);
	--k[0];
	token = ft_newtokens(all, REGISTER, -1);
	token->str = ft_strsub(all->line, i, all->i - i);
	if (k[0] > 0)
	{
		quick_pass(all);
		all->line[all->i] != SEPARATOR_CHAR ? ft_error(all, Syntactic, No_comma) : ++all->i;
		quick_pass(all);
	}
	ft_tokenspush(&all->temp, token);
	return (1);
}

int ft_dir(t_all *all, int *k)
{
	char		c;
	unsigned	i;
	t_tokens	*token;

	c = DIRECT_CHAR;
	quick_pass(all);
	if (all->line[all->i] != c)
		return (0);
	if (all->line[all->i + 1] == LABEL_CHAR)
	{
		++all->i;
		if (all->i + 1 ==  DIRECT_CHAR)
		{
			++all->i;
			checkmet(all, INDIRECT);
		}
		else checkmet(all, DIRECT);
		return (1);
	}
	++all->i;
	i = all->i;
	miniatoi(all);
	if (i - all->i == 0)
		return (0);
	--k[0];
	token = ft_newtokens(all, DIRECT, -1);
	token->str = ft_strsub(all->line, i - 1, all->i - i + 1);
	if (k[0] > 0)
	{
		quick_pass(all);
		all->line[all->i] != SEPARATOR_CHAR ? ft_error(all, Syntactic, No_comma) : ++all->i;
		quick_pass(all);
	}
	ft_tokenspush(&all->temp, token);
	return (1);
}

int ft_idir(t_all *all, int *k)
{
	unsigned i;
	t_tokens *token;

	quick_pass(all);
	if (all->line[all->i] == LABEL_CHAR)
	{
		checkmet(all, INDIRECT);
		return (1);
	}
	i = all->i;
	miniatoi(all);
	if (i - all->i == 0)
		return (0);
	--k[0];
	token = ft_newtokens(all, INDIRECT, -1);
	token->str = ft_strsub(all->line, i, all->i - i);
	if (k[0] > 0)
	{
		quick_pass(all);
		all->line[all->i] != SEPARATOR_CHAR ? ft_error(all, Syntactic, No_comma) : ++all->i;
		quick_pass(all);
	}
	ft_tokenspush(&all->temp, token);
	return (1);
}

void		ft_parseng(t_all *all, t_op a)
{
	char		*v;
	unsigned	j;
	int 		f;
	int			k;

	j = 0;
	k = a.arg_q - 1;
	all->i += ft_strlen((char *)a.cmd);
	while (j < 3)
	{
		all->line[all->i] == SEPARATOR_CHAR ? ++all->i : 0;
		f = 0;
		if (!a.arg_type[j])
			++j;
		else
			{
			v = tablica(a.arg_type[j]);
			quick_pass(all);
			if (v[0] == 1)
				f = ft_idir(all, &k);
			if (v[1] == 1 && !f)
				f = ft_dir(all, &k);
			if (v[2] == 1 && !f)
				f = ft_reg(all, &k);
			free(v);
			!f ? ft_error(all, Syntactic, Wrong_argument) : 0;
			++j;
		}
	}
	last_check(all, 0) ? ft_error(all, Syntactic, Odd_argument) : 0;
}

void			tokens(t_all *all)
{
	t_op		a;
	t_tokens	*token;
	int			i;

	quick_pass(all);
	i = -1;
	a = operations(all, &i);
	if (!a.cmd[0])
	{
		checkmet(all, LABEL);
		i = -1;
		quick_pass(all);
		if (!all->line[all->i])
		{
			ft_lstpush(&all->parsing, ft_lstnew_ptr(all->temp));
			all->temp = NULL;
			return ;
		}
		a = operations(all, &i);
	}
	if (a.cmd[0])
	{
		token = ft_newtokens(all, INSTRUCTION, i);
		token->str = ft_strsub((char *)a.cmd, 0, ft_strlen((char *)a.cmd));
		ft_tokenspush(&all->temp, token);
	}
	!a.cmd[0] ? ft_error(all, Syntactic, Uknown_instr) : ft_parseng(all, a);
}

void	parseng(t_all *all)
{
	while (checkform(all))
	{
		if (all->line)
		{
			quick_pass(all);
			tokens(all);
			all->temp ? ft_lstpush(&all->parsing, ft_lstnew_ptr(all->temp)) : 0;
			all->temp = NULL;
			free(all->line);
			all->line = NULL;
		}
	}
	all->i = 0;
	if (!all->parsing /*|| last_check(all, 1)*/)
		ft_error(all, Syntactic, No_last_line);
}