/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlabadie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 13:39:48 by dlabadie          #+#    #+#             */
/*   Updated: 2019/06/05 13:39:49 by dlabadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static unsigned int		calc_step(t_cursor *cursor, t_op *op)
{
	int				i;
	unsigned int	step;

	i = 0;
	step = 0;
	step += OP_CODE_LEN + (op->args_types_code ? ARGS_CODE_LEN : 0);
	while (i < g_op[INDEX(cursor->op_code)].args_num)
	{
		step += step_size(cursor->args_types[i], op);
		i++;
	}
	return (step);
}

static void				reload_cycles_to_exec(t_cursor *cursor, t_vm *vm)
{
	if (cursor->cycles_to_exec == 0)
	{
		cursor->op_code = vm->arena[cursor->pc];
		if (vm->arena[cursor->pc] >= 0x01 && vm->arena[cursor->pc] <= 0x10)
			cursor->cycles_to_exec = g_op[INDEX(cursor->op_code)].cycles;
	}
	if (cursor->cycles_to_exec > 0)
		cursor->cycles_to_exec--;
}

static void				pre_apply(t_cursor *cursor, t_vm *vm)
{
	t_op *op;

	reload_cycles_to_exec(cursor, vm);
	if (cursor->cycles_to_exec == 0)
	{
		op = NULL;
		if (cursor->op_code >= 0x01 && cursor->op_code <= 0x10)
			op = &g_op[INDEX(cursor->op_code)];
		if (op)
		{
			parse_types_code(vm, cursor, op);
			if (can_i_apply(cursor, vm, op))
				op->func(vm, cursor);
			else
				cursor->step += calc_step(cursor, op);
		}
		else
			cursor->step = OP_CODE_LEN;
		move_cursor(cursor);
	}
}

void					run(t_vm *vm)
{
	t_cursor *cursor;

	while (vm->cursors_num)
	{
		show_fight_field(vm);
		vm->cycles++;
		vm->cycles_after_check++;
		cursor = vm->cursors;
		while (cursor)
		{
			pre_apply(cursor, vm);
			cursor = cursor->next;
		}
		the_check(vm);
	}
}
