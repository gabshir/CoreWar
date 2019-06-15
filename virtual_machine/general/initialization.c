/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlabadie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 13:59:11 by dlabadie          #+#    #+#             */
/*   Updated: 2019/06/05 13:59:13 by dlabadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_vm		*init_vm(void)
{
	t_vm *vm;

	if (!(vm = (t_vm *)ft_memalloc(sizeof(t_vm))))
		print_error(MALLOC);
	vm->players_num = 0;
	vm->last_alive = NULL;
	vm->cursors = NULL;
	vm->cursors_num = 0;
	vm->lives_num = 0;
	vm->cycles = 0;
	vm->cycles_to_die = CYCLE_TO_DIE;
	vm->cycles_after_check = 0;
	vm->checks_num = 0;
	vm->dump_cycle = -1;
	vm->dump_print_mode = 0;
	vm->visu = 0;
	return (vm);
}

void		init_arena(t_vm *vm)
{
	int				id;
	unsigned int	pc;

	id = 1;
	pc = 0;
	while (id <= vm->players_num)
	{
		ft_memcpy(&(vm->arena[pc]), vm->players[INDEX(id)]->code, \
		(size_t)(vm->players[INDEX(id)]->code_size));
		pc += MEM_SIZE / vm->players_num;
		id++;
	}
}

t_cursor	*init_cursor(t_player *player, int pc)
{
	t_cursor		*cursor;

	if (!(cursor = (t_cursor *)ft_memalloc(sizeof(t_cursor))))
		print_error(MALLOC);
	cursor->carry = false;
	cursor->op_code = 0;
	cursor->last_live = 0;
	cursor->cycles_to_exec = 0;
	cursor->pc = pc;
	cursor->next = NULL;
	cursor->reg[INDEX(1)] = -(player->id);
	cursor->player = player;
	return (cursor);
}
