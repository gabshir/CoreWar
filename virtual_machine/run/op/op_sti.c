/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlabadie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 18:27:50 by dlabadie          #+#    #+#             */
/*   Updated: 2019/06/10 18:27:52 by dlabadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void				op_sti(t_vm *vm, t_cursor *cursor)
{
	t_register	reg;
	t_register	value;
	t_register	addr_1;
	t_register	addr_2;

	cursor->step += OP_CODE_LEN + ARGS_CODE_LEN;
	reg = vm->arena[get_address(cursor->pc + cursor->step)];
	value = cursor->reg[INDEX(reg)];
	cursor->step += REG_LEN;
	if (cursor->args_types[SECOND] & (T_REG | T_DIR | T_IND))
		addr_1 = g_gets[cursor->args_types[SECOND] / 2].get(vm, cursor);
	else
		addr_1 = 0;
	if (cursor->args_types[THIRD] & (T_REG | T_DIR | T_IND))
		addr_2 = g_gets[cursor->args_types[THIRD] / 2].get(vm, cursor);
	else
		addr_2 = 0;
	ito_arena(vm->arena,
			(cursor->pc + ((addr_1 + addr_2) % IDX_MOD)), value, DIR_SIZE);
}
