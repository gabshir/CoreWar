/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_xor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlabadie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 18:28:08 by dlabadie          #+#    #+#             */
/*   Updated: 2019/06/10 18:28:09 by dlabadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void				op_xor(t_vm *vm, t_cursor *cursor)
{
	t_register	value_1;
	t_register	value_2;
	t_register	value;
	t_register	reg;

	cursor->step += OP_CODE_LEN + ARGS_CODE_LEN;
	if (cursor->args_types[FIRST] & (T_REG | T_DIR | T_IND))
		value_1 = g_gets[cursor->args_types[FIRST] / 2].get(vm, cursor);
	else
		value_1 = 0;
	if (cursor->args_types[SECOND] & (T_REG | T_DIR | T_IND))
		value_2 = g_gets[cursor->args_types[SECOND] / 2].get(vm, cursor);
	else
		value_2 = 0;
	value = value_1 ^ value_2;
	cursor->carry = (char)(!value);
	reg = vm->arena[get_address(cursor->pc + cursor->step)];
	cursor->reg[INDEX(reg)] = value;
	cursor->step += REG_LEN;
}
