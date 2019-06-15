/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlabadie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 18:28:17 by dlabadie          #+#    #+#             */
/*   Updated: 2019/06/10 18:28:19 by dlabadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void				op_zjmp(t_vm *vm, t_cursor *cursor)
{
	t_register addr;

	cursor->step += OP_CODE_LEN;
	if (cursor->args_types[FIRST] & (T_REG | T_DIR | T_IND))
		addr = g_gets[cursor->args_types[FIRST] / 2].get(vm, cursor);
	else
		addr = 0;
	if (cursor->carry)
	{
		cursor->pc = get_address(cursor->pc + (addr % IDX_MOD));
		cursor->step = 0;
	}
}
