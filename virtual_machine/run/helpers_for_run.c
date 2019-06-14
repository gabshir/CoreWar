/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_for_run.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlabadie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 14:57:01 by dlabadie          #+#    #+#             */
/*   Updated: 2019/06/05 14:57:02 by dlabadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

unsigned int	step_size(t_byte arg_type, t_op *op)
{
	if (arg_type & T_REG)
		return (REG_LEN);
	else if (arg_type & T_DIR)
		return (op->t_dir_size);
	else if (arg_type & T_IND)
		return (IND_SIZE);
	return (0);
}

int				btoi_in_arena(const t_byte *arena, int addr, int size)
{
	int			result;
	char		sign;
	int			i;

	result = 0;
	sign = (char)(arena[get_address(addr)] & 0x80);
	i = 0;
	while (size)
	{
		if (sign)
			result += ((arena[get_address(addr + \
			size - 1)] ^ 0xFF) << (i++ * 8));
		else
			result += arena[get_address(addr + size - 1)] << (i++ * 8);
		size--;
	}
	if (sign)
		result = ~(result);
	return (result);
}

void			ito_arena(t_byte *arena, int addr, int value,
								int size)
{
	t_byte i;

	i = 0;
	while (size)
	{
		arena[get_address(addr + size - 1)] = \
		(t_byte)((value >> (i * 8)) & 0xFF);
		i++;
		size--;
	}
}
