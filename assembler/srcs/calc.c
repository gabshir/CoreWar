/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 00:29:36 by gabshire          #+#    #+#             */
/*   Updated: 2019/06/11 08:50:56 by gabshire         ###   ########.fr       */
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
		c = (uint8_t)((l >> i) & 0xFF);
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

int 		label_distance(t_tokens *token, t_all *all)
{
	t_tokens	*copyscan;
	int			r;
	t_list		*parseng;

	parseng = all->parsing;
	while (parseng)
	{
		copyscan = parseng->content;
		if ((!(ft_strcmp(copyscan->str, token->str))) && copyscan->tp == LABEL)
			break ;
		parseng = parseng->next;
	}
	!parseng ? ft_error(all, Semantic, Label_not_found) : 0;
	if (copyscan->t_r > token->t_r)
		r = copyscan->t_r;
	else
		{
			r = token->t_r - copyscan->t_r - 1;
			r = -r;
		}
	return (r);
}

void dop_code(int s, t_all *all, size_t size)
{
	int f;

	f = s < 0 ? 1 : 0;
	s < 0 ? s = -s  : 0;
	translate_to_bytecode(all, size, s);
	if (f == 1)
	{
		all->source[all->i - 2] =~ all->source[all->i];
		all->source[all->i - 1] =~ all->source[all->i - 1];
		all->source[all->i - 1] += 1;
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
				translate_to_bytecode(all,copytoken->size, r);
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
			copy->tp == LABEL || copy->tp == DIRLABEL
			|| copy->tp == INDIRLABEL ? copy->t_r = size : 0;
			size += copy->size;
			ft_printf("%s ", copy->str);
			copy = copy->next;
		}
		ft_printf("\n");
		parseng = parseng->next;
	}
	return (size);
}


void		translate_into_byte_code(t_all *all)
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
	write(all->fd, all->source, size);
}
