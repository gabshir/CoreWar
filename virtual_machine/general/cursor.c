/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlabadie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 10:56:24 by dlabadie          #+#    #+#             */
/*   Updated: 2019/06/06 10:56:26 by dlabadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_cursor	*erase_cursor(t_cursor *previous, t_cursor **delete)
{
	t_cursor	*current;

	if (previous)
		previous->next = previous->next->next;
	current = (*delete)->next;
	ft_memdel((void **)delete);
	return (current);
}

void		add_cursor(t_cursor **list, t_cursor *new)
{
	if (new)
		new->next = *list;
	*list = new;
}

void		set_cursors(t_vm *vm)
{
	int				id;
	unsigned int	pc;

	id = 1;
	pc = 0;
	while (id <= vm->players_num)
	{
		add_cursor(&(vm->cursors), init_cursor(vm->players[INDEX(id)], pc));
		vm->cursors_num++;
		pc += MEM_SIZE / vm->players_num;
		id++;
	}
}

void		move_cursor(t_cursor *cursor)
{
	cursor->pc += cursor->step;
	cursor->pc = get_address(cursor->pc);
	cursor->step = 0;
	ft_bzero(cursor->args_types, 3);
}

t_cursor	*duplicate_cursor(t_cursor *cursor, int addr)
{
	t_cursor	*new;
	int			i;

	addr = get_address(cursor->pc + addr);
	new = init_cursor(cursor->player, addr);
	i = 0;
	while (i < REG_NUMBER)
	{
		new->reg[i] = cursor->reg[i];
		i++;
	}
	new->carry = cursor->carry;
	new->last_live = cursor->last_live;
	return (new);
}
