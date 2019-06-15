/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlabadie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 18:27:59 by dlabadie          #+#    #+#             */
/*   Updated: 2019/06/10 18:28:00 by dlabadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void				op_sub(t_vm *vm, t_cursor *cursor)
{
	t_register	first;
	t_register	second;
	t_register	third;
	t_register	value;

	cursor->step += (OP_CODE_LEN + ARGS_CODE_LEN);
	first = vm->arena[get_address(cursor->pc + cursor->step)];
	cursor->step += REG_LEN;
	second = vm->arena[get_address(cursor->pc + cursor->step)];
	cursor->step += REG_LEN;
	value = cursor->reg[INDEX(first)] - cursor->reg[INDEX(second)];
	cursor->carry = (char)(!value);
	third = vm->arena[get_address(cursor->pc + cursor->step)];
	cursor->reg[INDEX(third)] = value;
	cursor->step += REG_LEN;
}
