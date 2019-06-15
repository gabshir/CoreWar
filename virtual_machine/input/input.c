/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlabadie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 13:44:22 by dlabadie          #+#    #+#             */
/*   Updated: 2019/06/05 13:44:23 by dlabadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_vm			*input(int argc, char **argv)
{
	t_vm		*vm;
	t_parser	parser;

	parser.index = argc - 1;
	parser.arg = argv + 1;
	parser.player = NULL;
	vm = init_vm();
	while (parser.index >= 1)
		parse_flags(&parser, vm);
	if (vm->players_num < 1 || vm->players_num > MAX_PLAYERS)
		print_error(ANY);
	reload_players_list(vm, parser.player);
	init_arena(vm);
	set_cursors(vm);
	return (vm);
}
