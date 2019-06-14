/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlabadie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 18:12:56 by dlabadie          #+#    #+#             */
/*   Updated: 2019/06/10 18:12:58 by dlabadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void				op_lld(t_vm *vm, t_cursor *cursor)
{
	t_register	value;
	t_register	reg;

	cursor->step += (OP_CODE_LEN + ARGS_CODE_LEN);
	if (cursor->args_types[FIRST] / 2 == 2)
	{
		value = btoi_in_arena(vm->arena, cursor->pc + \
		btoi_in_arena(vm->arena, cursor->pc + \
		cursor->step, IND_SIZE), DIR_SIZE);
	}
	else if (cursor->args_types[FIRST] & (T_REG | T_DIR | T_IND))
		value = g_gets[cursor->args_types[FIRST] / 2].get(vm, cursor);
	else
		value = 0;
	cursor->carry = (char)(!value);
	reg = vm->arena[get_address(cursor->pc + cursor->step)];
	cursor->reg[INDEX(reg)] = value;
	cursor->step += REG_LEN;
}
