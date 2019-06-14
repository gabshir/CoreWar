/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_operation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlabadie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 18:50:49 by dlabadie          #+#    #+#             */
/*   Updated: 2019/06/05 18:50:53 by dlabadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_byte		get_arg_type(t_byte args_types_code, t_byte num)
{
	t_byte code_of_type;

	if (num == FIRST)
		code_of_type = (t_byte)((args_types_code & 0xC0) >> 6);
	else if (num == SECOND)
		code_of_type = (t_byte)((args_types_code & 0x30) >> 4);
	else if (num == THIRD)
		code_of_type = (t_byte)((args_types_code & 0xC) >> 2);
	else
		return (0);
	return (g_arg_code[INDEX(code_of_type)]);
}

void				parse_types_code(t_vm *vm, t_cursor *cursor, t_op *op)
{
	t_byte args_types_code;

	if (op->args_types_code)
	{
		args_types_code = vm->arena[get_address(cursor->pc + 1)];
		if (op->args_num >= 1)
			cursor->args_types[INDEX(1)] = get_arg_type(args_types_code, FIRST);
		if (op->args_num >= 2)
			cursor->args_types[INDEX(2)] = \
			get_arg_type(args_types_code, SECOND);
		if (op->args_num >= 3)
			cursor->args_types[INDEX(3)] = get_arg_type(args_types_code, THIRD);
	}
	else
		cursor->args_types[0] = op->args_types[0];
}

char				can_i_apply(t_cursor *cursor, t_vm *vm, t_op *op)
{
	int				i;
	unsigned int	step;
	t_byte			reg;

	i = 0;
	step = (OP_CODE_LEN + (op->args_types_code ? ARGS_CODE_LEN : 0));
	while (i < op->args_num)
	{
		if (!(cursor->args_types[i] & op->args_types[i]))
			return (false);
		reg = vm->arena[get_address(cursor->pc + step)];
		if ((cursor->args_types[i] == T_REG) && !(reg >= 1 && reg <= \
		REG_NUMBER))
			return (false);
		step += step_size(cursor->args_types[i], op);
		i++;
	}
	return (true);
}
