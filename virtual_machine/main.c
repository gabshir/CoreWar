/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlabadie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 11:57:07 by dlabadie          #+#    #+#             */
/*   Updated: 2019/06/05 11:57:08 by dlabadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			main(int argc, char **argv)
{
	t_vm *vm;

	if (argc >= 2)
	{
		vm = input(argc, argv);
		print_introducing(vm->players, vm->players_num);
		run(vm);
		if (vm->visu)
			display_winner(vm);
		else
			print_winner(vm);
		free_vm(&vm);
	}
	else
		print_usage();
	return (0);
}
