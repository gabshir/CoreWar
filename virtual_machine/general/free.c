/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlabadie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 14:14:00 by dlabadie          #+#    #+#             */
/*   Updated: 2019/06/05 14:14:01 by dlabadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	free_players(t_player **players, int players_num)
{
	int id;

	id = 1;
	while (id <= players_num)
	{
		ft_strdel(&(players[INDEX(id)]->name));
		ft_strdel(&(players[INDEX(id)]->comment));
		ft_memdel((void **)&(players[INDEX(id)]->code));
		ft_memdel((void **)&players[INDEX(id)]);
		id++;
	}
}

static void	free_cursors(t_cursor **list)
{
	t_cursor	*current;
	t_cursor	*delete;

	current = *list;
	while (current)
	{
		delete = current;
		current = current->next;
		ft_memdel((void **)&delete);
	}
	*list = NULL;
}

void		free_vm(t_vm **vm)
{
	free_players((*vm)->players, (*vm)->players_num);
	free_cursors(&((*vm)->cursors));
	ft_memdel((void **)vm);
}
