/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 00:29:36 by gabshire          #+#    #+#             */
/*   Updated: 2019/06/12 22:42:27 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	translate_to_bytecode(t_all *all, size_t size, unsigned l)
{
	int8_t		i;
	size_t 		k;
	char		c;

	i = 0;
	k = size;
	while (size)
	{
		c = (char)((l >> i) & 0xFF);
		all->source[all->i + size - 1] = c;
		i += 8;
		--size;
	}
	all->i += k;
}

void	name_and_comment(t_all *all, int f)
{
	char *str;
	unsigned start;

	str = f == 1 ? all->prog_name : all->comment;
	start = all->i;
	all->i += f == 1 ? PROG_NAME_LENGTH : COMMENT_LENGTH;
	while(*str)
	{
		all->source[start] = *str;
		++start;
		++str;
	}
	all->i += 4;
}

void		instruktion_to_bytecode(t_tokens *token, t_all *all)
{
	t_tokens	*copy;
	unsigned 	i;
	char		c;

	translate_to_bytecode(all, 1, token->operation + 1);
	if (token->size == 2)
	{
		copy = token;
		copy = copy->next;
		i = 0;
		c = all->source[all->i];
		while(copy)
		{
			copy->tp == DIRECT || copy->tp == DIRLABEL ? c |= 1 << (7 - i) : 0;
			copy->tp == REGISTER ? c |= 1 << (6 - i) : 0;
			if (copy->tp == INDIRECT || copy->tp == INDIRLABEL)
			{
				c |= 1 << (7 - i);
				c |= 1 << (6 - i);
			}
			copy = copy->next;
			i += 2;
		}
		all->source[all->i++] = c;
	}
}

int 		label_distanse_mp(t_tokens *token, t_tokens *copyscan,
		int *k, t_tokens *s)
{
	int f;

	f = 0;
	if (!ft_strcmp(copyscan->str, token->str) && (copyscan->tp == DIRLABEL
	|| copyscan->tp == INDIRLABEL) && copyscan->st == s->st)
		{
			k[0] = 0;
			f = 1;
		}
	return (f);
}

int 		label_distanse_m(t_tokens *token, t_list *parseng,
		t_all *all, t_tokens *s)
{
	t_tokens	*copyscan;
	int			r;
	int			f;
	int			k;

	f = 0;
	r = 0;
	k = 0;
	while (parseng)
	{
		copyscan = parseng->content;
		while (copyscan)
		{
			k += copyscan->size;
			if ((f = label_distanse_mp(token, copyscan, &k, s)))
				break ;
			copyscan = copyscan->next;
		}
		r += k;
		k = 0;
		if (f)
			break;
		parseng = parseng->next;
	}
	!parseng ? ft_error(all, Semantic, Label_not_found) : 0;
	return (-r);
}

int 		label_distanse_p(t_list *parseng, t_all *all, t_tokens *token)
{
	t_tokens	*copyscan;
	int			r;
	int			f;
	char		*str;

	f = 0;
	r = 0;
	copyscan = parseng->content;
	str = token->str;
	while (copyscan)
	{
		r += copyscan->size;
		copyscan = copyscan->next;
	}
	parseng = parseng->next;
	while (parseng)
	{
		copyscan = parseng->content;
		while (copyscan)
		{
			r += copyscan->size;
			if (!ft_strcmp(copyscan->str, str) && copyscan->tp == LABEL)
			{
				f = 1;
				break ;
			}
			copyscan = copyscan->next;
		}
		if (f)
			break;
		parseng = parseng->next;
	}
	!parseng ? ft_error(all, Semantic, Label_not_found) : 0;
	return (r);
}

int 		label_distance(t_tokens *token, t_all *all)
{
	t_tokens	*copyscan;
	int			r;
	t_list		*parseng;

	parseng = all->parsing;
	copyscan = parseng->content;
	while (parseng)
	{
		copyscan = parseng->content;
		if ((copyscan->st == token->st)
		|| (!ft_strcmp(copyscan->str, token->str) && (copyscan->tp == LABEL
		|| copyscan->tp == DIRLABEL || copyscan->tp == INDIRLABEL)))
			break ;
		parseng = parseng->next;
	}
	if (token->st > copyscan->st)
		r = label_distanse_m(copyscan, parseng, all, token);
	else
		r = label_distanse_p(parseng, all, token);
	return (r);
}

void dop_code(int s, t_all *all, size_t size)
{
	int				f;
	unsigned char	c;

	f = s < 0 ? 1 : 0;
	s < 0 ? s = -s  : 0;
	translate_to_bytecode(all, size, s);
	if (f == 1)
	{
		all->source[all->i - 2] =~ all->source[all->i - 2];
		c =~ all->source[all->i - 1];
		if (c == 0xff)
			all->source[all->i - 2] += 1;
		c += 1;
		all->source[all->i - 1] = c;
	}
}

void		operation_to_bytecode(t_all *all)
{
	t_list		*copy;
	t_tokens	*token;
	t_tokens	*copytoken;
	int			r;

	copy = all->parsing;
	while(copy)
	{
		token = copy->content;
		copytoken = token;
		while (copytoken)
		{
			if (copytoken->tp == INSTRUCTION)
				instruktion_to_bytecode(copytoken, all);
			else if (copytoken->tp == REGISTER)
			{
				r = ft_atoi(copytoken->str);
				translate_to_bytecode(all, copytoken->size, r);
			}
			else if (copytoken->tp == DIRECT || copytoken->tp == INDIRECT)
				dop_code(ft_atoi(copytoken->str), all, copytoken->size);
			else if (copytoken->tp == DIRLABEL || copytoken->tp == INDIRLABEL)
			{
				r = label_distance(copytoken, all);
				dop_code(r, all, copytoken->size);
			}
			copytoken = copytoken->next;
		}
		copy = copy->next;
	}
}

unsigned	size_soure(t_list *parseng)
{
	unsigned	size;
	t_tokens	*token;
	t_tokens	*copy;

	size = 0;
	while(parseng)
	{
		token = parseng->content;
		copy = token;
		while(copy)
		{
			size += copy->size;
			copy = copy->next;
		}
		parseng = parseng->next;
	}
	return (size);
}


void		translate_into_byte_code(t_all *all, char *file_name)
{
	unsigned	size;

	all->prog_size = size_soure(all->parsing);
	size = all->prog_size + PROG_NAME_LENGTH + COMMENT_LENGTH + 16;
	if (!(all->source = ft_strnew(size)))
		return ;
	all->i = 0;
	translate_to_bytecode(all, 4, all->magic);
	name_and_comment(all, 1);
	translate_to_bytecode(all, 4, all->prog_size);
	name_and_comment(all, 0);
	operation_to_bytecode(all);
	if (all->errors)
		print_errors(all, file_name);
	write(all->fd, all->source, size);
}
