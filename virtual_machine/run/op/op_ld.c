/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlabadie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 18:11:22 by dlabadie          #+#    #+#             */
/*   Updated: 2019/06/10 18:11:24 by dlabadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void				op_ld(t_vm *vm, t_cursor *cursor)
{
	t_register	value;
	t_register	reg;

	cursor->step += (OP_CODE_LEN + ARGS_CODE_LEN);
	if (cursor->args_types[FIRST] & (T_REG | T_DIR | T_IND))
		value = g_gets[cursor->args_types[FIRST] / 2].get(vm, cursor);
	else
		value = 0;
	cursor->carry = (char)(!value);
	reg = vm->arena[get_address(cursor->pc + cursor->step)];
	cursor->reg[INDEX(reg)] = value;
	cursor->step += REG_LEN;
}
