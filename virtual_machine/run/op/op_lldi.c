/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlabadie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 18:13:04 by dlabadie          #+#    #+#             */
/*   Updated: 2019/06/10 18:13:06 by dlabadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void				op_lldi(t_vm *vm, t_cursor *cursor)
{
	t_register	value_1;
	t_register	value_2;
	t_register	reg;

	value_1 = 0;
	value_2 = 0;
	cursor->step += OP_CODE_LEN + ARGS_CODE_LEN;
	if (cursor->args_types[FIRST] / 2 == 2)
	{
		value_1 = btoi_in_arena(vm->arena, cursor->pc + btoi_in_arena(\
		vm->arena, cursor->pc + cursor->step, IND_SIZE), DIR_SIZE);
	}
	else if (cursor->args_types[FIRST] & (T_REG | T_DIR | T_IND))
		value_1 = g_gets[cursor->args_types[FIRST] / 2].get(vm, cursor);
	if (cursor->args_types[SECOND] / 2 == 2)
	{
		value_2 = btoi_in_arena(vm->arena, cursor->pc + btoi_in_arena(\
		vm->arena, cursor->pc + cursor->step, IND_SIZE), DIR_SIZE);
	}
	else if (cursor->args_types[SECOND] & (T_REG | T_DIR | T_IND))
		value_2 = g_gets[cursor->args_types[SECOND] / 2].get(vm, cursor);
	reg = vm->arena[get_address(cursor->pc + cursor->step)];
	cursor->reg[INDEX(reg)] = btoi_in_arena(vm->arena,
			cursor->pc + (value_1 + value_2), DIR_SIZE);
	cursor->step += REG_LEN;
}
