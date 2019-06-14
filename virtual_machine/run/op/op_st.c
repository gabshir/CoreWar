/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlabadie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 18:26:48 by dlabadie          #+#    #+#             */
/*   Updated: 2019/06/10 18:26:50 by dlabadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void				op_st(t_vm *vm, t_cursor *cursor)
{
	t_register	reg;
	t_register	value;
	t_register	addr;

	cursor->step += (OP_CODE_LEN + ARGS_CODE_LEN);
	reg = vm->arena[get_address(cursor->pc + cursor->step)];
	value = cursor->reg[INDEX(reg)];
	cursor->step += REG_LEN;
	if (cursor->args_types[1] == T_REG)
	{
		addr = vm->arena[get_address(cursor->pc + cursor->step)];
		cursor->reg[INDEX(addr)] = value;
		cursor->step += REG_LEN;
	}
	else
	{
		addr = btoi_in_arena(vm->arena,
							cursor->pc + cursor->step, IND_SIZE);
		ito_arena(vm->arena, cursor->pc + (addr % IDX_MOD),
				value, DIR_SIZE);
		cursor->step += IND_SIZE;
	}
}
