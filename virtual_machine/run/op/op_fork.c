/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlabadie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 18:11:14 by dlabadie          #+#    #+#             */
/*   Updated: 2019/06/10 18:11:15 by dlabadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void				op_fork(t_vm *vm, t_cursor *cursor)
{
	t_register		addr;
	t_cursor		*new;

	cursor->step += OP_CODE_LEN;
	if (cursor->args_types[FIRST] & (T_REG | T_DIR | T_IND))
		addr = g_gets[cursor->args_types[FIRST] / 2].get(vm, cursor);
	else
		addr = 0;
	new = duplicate_cursor(cursor, addr % IDX_MOD);
	add_cursor(&(vm->cursors), new);
	vm->cursors_num++;
}
