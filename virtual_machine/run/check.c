/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlabadie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 15:45:12 by dlabadie          #+#    #+#             */
/*   Updated: 2019/06/06 15:45:13 by dlabadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		erase_died_cursors(t_vm *vm)
{
	t_cursor	*current;
	t_cursor	*previous;

	previous = NULL;
	current = vm->cursors;
	while (current)
	{
		if (vm->cycles_to_die <= 0 || \
		vm->cycles - current->last_live >= vm->cycles_to_die)
		{
			vm->cursors_num--;
			if (vm->cursors == current)
				vm->cursors = current->next;
			current = erase_cursor(previous, &current);
		}
		else
		{
			previous = current;
			current = current->next;
		}
	}
}

void			the_check(t_vm *vm)
{
	int		i;

	if (vm->cycles_to_die == vm->cycles_after_check
		|| vm->cycles_to_die <= 0)
	{
		vm->checks_num++;
		erase_died_cursors(vm);
		if (vm->checks_num == MAX_CHECKS || vm->lives_num >= NBR_LIVE)
		{
			vm->cycles_to_die -= CYCLE_DELTA;
			vm->checks_num = 0;
		}
		i = 0;
		while (i < vm->players_num)
		{
			vm->players[i]->previous_lives_num = \
			vm->players[i]->current_lives_num;
			vm->players[i]->current_lives_num = 0;
			i++;
		}
		vm->lives_num = 0;
		vm->cycles_after_check = 0;
	}
}
