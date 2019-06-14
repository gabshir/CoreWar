/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 04:17:13 by gabshire          #+#    #+#             */
/*   Updated: 2019/06/13 06:22:14 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	free_parseng(t_all *all)
{
	t_tokens	*token;
	t_tokens	*next;
	t_list		*next_parsing;

	while (all->parsing)
	{
		token = all->parsing->content;
		while (token)
		{
			free(token->str);
			token->str = NULL;
			next = token->next;
			free(token);
			token = next;
		}
		next_parsing = all->parsing->next;
		free(all->parsing);
		all->parsing = NULL;
		all->parsing = next_parsing;
	}
}

void		global_free(t_all *all)
{
	unsigned	i;
	t_error		*next;

	i = 0;
	free(all->source);
	while (all->split[i])
	{
		free(all->split[i]);
		all->split[i] = NULL;
		++i;
	}
	free(all->split);
	all->split = NULL;
	free_parseng(all);
	if (all->errors)
	{
		while (all->errors)
		{
			next = all->errors->next;
			free(all->errors);
			all->errors = NULL;
			all->errors = next;
		}
	}
}
