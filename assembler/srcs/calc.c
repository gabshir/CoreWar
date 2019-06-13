/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 00:29:36 by gabshire          #+#    #+#             */
/*   Updated: 2019/06/13 03:03:42 by gabshire         ###   ########.fr       */
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
