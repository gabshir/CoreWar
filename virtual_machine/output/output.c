/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlabadie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 13:44:31 by dlabadie          #+#    #+#             */
/*   Updated: 2019/06/05 13:44:33 by dlabadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		print_introducing(t_player **players, int players_num)
{
	int id;

	id = 1;
	ft_printf("Introducing contestants...\n");
	while (id <= players_num)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
	id,
	players[INDEX(id)]->code_size,
	players[INDEX(id)]->name,
	players[INDEX(id)]->comment);
		id++;
	}
}

void		print_winner(t_vm *vm)
{
	ft_printf("Contestant %d, \"%s\", has won !\n", \
	FT_ABS(vm->last_alive->id), vm->last_alive->name);
}

void		print_usage(void)
{
	ft_printf("Usage: ./corewar [ -dump <num> ] "
	"[-n <num>] <champion.cor> <...>\n");
	exit(0);
}

void		print_error(char *error)
{
	ft_putendl_fd(error, 2);
	exit(0);
}
