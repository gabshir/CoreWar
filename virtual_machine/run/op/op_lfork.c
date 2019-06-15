/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlabadie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 18:12:32 by dlabadie          #+#    #+#             */
/*   Updated: 2019/06/10 18:12:34 by dlabadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void				op_lfork(t_vm *vm, t_cursor *cursor)
{
	t_register		addr;
	t_cursor		*new;

	cursor->step += OP_CODE_LEN;
	addr = g_gets[cursor->args_types[FIRST] / 2].get(vm, cursor);
	new = duplicate_cursor(cursor, addr);
	add_cursor(&(vm->cursors), new);
	vm->cursors_num++;
}
