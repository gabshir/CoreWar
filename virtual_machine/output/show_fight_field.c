/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_fight_field.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlabadie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 15:06:39 by dlabadie          #+#    #+#             */
/*   Updated: 2019/06/06 15:06:41 by dlabadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		print_arena(t_byte *arena, int print_mode)
{
	int	i;
	int	j;

	i = 0;
	while (i < MEM_SIZE)
	{
		ft_printf("%.4p : ", i);
		j = 0;
		while (j < print_mode)
		{
			ft_printf("%.2x ", arena[i + j]);
			j++;
		}
		ft_printf("\n");
		i += print_mode;
	}
}

void		show_fight_field(t_vm *vm)
{
	if (vm->dump_cycle == vm->cycles)
	{
		print_arena(vm->arena, vm->dump_print_mode);
		exit(0);
	}
	if (vm->visu == true)
	{
		print_visu(vm);
	}
}
