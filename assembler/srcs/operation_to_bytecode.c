/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_to_bytecode.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 03:43:59 by gabshire          #+#    #+#             */
/*   Updated: 2019/06/15 02:59:55 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		instruktion_to_bytecode(t_tokens *token, t_all *all)
{
	t_tokens	*copy;
	unsigned	i;
	char		c;

	translate_to_bytecode(all, 1, token->operation + 1);
	if (token->size == 2)
	{
		copy = token;
		copy = copy->next;
		i = 0;
		c = all->source[all->i];
		while (copy)
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

static void		convert_token_to_bytecode(t_all *all, t_tokens *copytoken)
{
	if (copytoken->tp == INSTRUCTION)
		instruktion_to_bytecode(copytoken, all);
	else if (copytoken->tp == REGISTER)
		translate_to_bytecode(all, copytoken->size, ft_atoi(copytoken->str));
	else if (copytoken->tp == DIRECT || copytoken->tp == INDIRECT)
		translate_to_bytecode(all, copytoken->size, ft_atoi(copytoken->str));
	else if (copytoken->tp == DIRLABEL || copytoken->tp == INDIRLABEL)
		translate_to_bytecode(all, copytoken->size, \
			label_distance(copytoken, all));
}

void			operation_to_bytecode(t_all *all)
{
	t_list		*copy;
	t_tokens	*token;
	t_tokens	*copytoken;

	copy = all->parsing;
	while (copy)
	{
		token = copy->content;
		copytoken = token;
		while (copytoken)
		{
			convert_token_to_bytecode(all, copytoken);
			copytoken = copytoken->next;
		}
		copy = copy->next;
	}
}
