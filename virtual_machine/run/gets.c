/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gets.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlabadie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 18:07:43 by dlabadie          #+#    #+#             */
/*   Updated: 2019/06/10 18:07:45 by dlabadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int				get_address(int addr)
{
	return ((addr % MEM_SIZE < 0) ? ((addr % \
	MEM_SIZE) + MEM_SIZE) : (addr % MEM_SIZE));
}

t_register		get_reg(t_vm *vm, t_cursor *cursor)
{
	int		value;

	value = cursor->reg[INDEX(vm->arena[\
	get_address(cursor->pc + cursor->step)])];
	cursor->step += REG_LEN;
	return (value);
}

t_register		get_dir(t_vm *vm, t_cursor *cursor)
{
	int		value;
	t_byte	step;

	step = g_op[INDEX(cursor->op_code)].t_dir_size;
	value = btoi_in_arena(vm->arena, cursor->pc + cursor->step, step);
	cursor->step += step;
	return (value);
}

t_register		get_ind(t_vm *vm, t_cursor *cursor)
{
	int		value;

	value = btoi_in_arena(vm->arena, cursor->pc + \
	(btoi_in_arena(vm->arena, cursor->pc + cursor->step, IND_SIZE) % \
	IDX_MOD), DIR_SIZE);
	cursor->step += IND_SIZE;
	return (value);
}
