/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wgueren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 18:37:17 by wgueren           #+#    #+#             */
/*   Updated: 2019/06/10 18:37:29 by wgueren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	print_visu(t_vm *vm)
{
	info_joueur(vm);
	print_arena_visu(vm);
	mvprintw(50, 198, "Cycle : %d", vm->cycles);
	mvprintw(52, 198, "Cycle to die : %d", vm->cycles_to_die);
	mvprintw(53, 198, "Cycle delta : %d", CYCLE_DELTA);
	mvprintw(54, 198, "Lives : %d", vm->lives_num);
	mvprintw(55, 198, "Checks : %d / %d", vm->checks_num, MAX_CHECKS);
	usleep(10000);
	refresh();
}

void	info_joueur(t_vm *vm)
{
	int		i;
	int		z;
	int		c;

	i = 0;
	z = 0;
	c = 0;
	while (i < vm->players_num)
	{
		if (vm->players[i]->id == (vm->players_num - \
		(vm->players_num - vm->players[i]->id)))
		{
			attron(COLOR_PAIR(1 + c));
			mvprintw(3 + z, 198, "Player %d:", vm->players[i]->id);
			attroff(COLOR_PAIR(1 + c));
			mvprintw(4 + z, 198, vm->players[i]->name);
			mvprintw(5 + z, 198, "Last live: %d", vm->players[i]->last_live);
		}
		i++;
		z = z + 10;
		c++;
	}
}

void	init_colors(void)
{
	init_color(5, 250, 250, 250);
	init_pair(1, 1, COLOR_BLACK);
	init_pair(2, 4, COLOR_BLACK);
	init_pair(3, 6, COLOR_BLACK);
	init_pair(4, 3, COLOR_BLACK);
	init_pair(5, 0, COLOR_RED);
	init_pair(6, 0, COLOR_BLUE);
	init_pair(7, 0, COLOR_CYAN);
	init_pair(8, 0, COLOR_YELLOW);
	init_pair(9, 5, COLOR_BLACK);
	init_pair(10, 0, COLOR_MAGENTA);
}

t_visu	init_visu(t_vm *vm)
{
	t_visu visu;

	if (vm->visu == false)
		print_error("wrong case with visual mode");
	initscr();
	getmaxyx(stdscr, visu.row, visu.col);
	if (visu.row <= 64 || visu.col <= 256)
	{
		clear();
		endwin();
		ft_printf("Make terminal more pls.\n");
		exit(0);
	}
	start_color();
	init_colors();
	return (visu);
}
