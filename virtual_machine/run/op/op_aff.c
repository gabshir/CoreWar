/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 18:10:12 by dlabadie          #+#    #+#             */
/*   Updated: 2019/06/14 22:33:15 by jwillem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	op_aff(t_vm *vm, t_cursor *cursor)
{
	t_register	reg;
	t_register	value;

	cursor->step += (OP_CODE_LEN + ARGS_CODE_LEN);
	reg = vm->arena[get_address(cursor->pc + cursor->step)];
	value = cursor->reg[INDEX(reg)];
	cursor->step += REG_LEN;
	if (vm->aff)
		ft_printf("Aff: %c\n", (char)value);
}
