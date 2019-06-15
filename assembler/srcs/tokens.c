/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabshire <gabshire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 17:49:19 by gabshire          #+#    #+#             */
/*   Updated: 2019/06/15 02:59:55 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_tokens	*ft_newtokens(t_all *all, t_type tp, int o, char size)
{
	t_tokens	*new;

	if (!(new = (t_tokens*)malloc(sizeof(t_tokens))))
		return (NULL);
	new->str = NULL;
	new->next = NULL;
	new->st = all->st;
	new->i = all->i;
	new->tp = tp;
	new->operation = o;
	new->size = size;
	return (new);
}

void		ft_tokenspush(t_tokens **alst, t_tokens *new)
{
	t_tokens *list;

	if (!new || !alst)
		return ;
	if (*alst)
	{
		list = *alst;
		while (list->next)
			list = list->next;
		list->next = new;
	}
	else
		*alst = new;
}
