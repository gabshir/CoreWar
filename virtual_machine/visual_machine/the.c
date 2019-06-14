/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wgueren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 18:37:42 by wgueren           #+#    #+#             */
/*   Updated: 2019/06/10 18:37:45 by wgueren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#define MAX_COLOR_NUM 4

int				is_carry_here(t_vm *vm, int i)
{
	t_cursor	*cur;
	int			j;

	j = 0;
	cur = vm->cursors;
	while (cur)
	{
		if (cur->pc == i)
			return (j);
		j++;
		cur = cur->next;
	}
	return (-1);
}

static void		print_arena_content(t_vm *vm, int i, int y, int x)
{
	int id;

	id = is_carry_here(vm, i);
	if (id == -2)
	{
		attron(COLOR_PAIR(3));
		mvprintw(y, x, "%02x", ARENA[i]);
		attroff(COLOR_PAIR(3));
	}
	if (id != -1)
	{
		attron(COLOR_PAIR(id % MAX_COLOR_NUM));
		mvprintw(y, x, "%02x", ARENA[i]);
		attroff(COLOR_PAIR(id % MAX_COLOR_NUM));
	}
	else
	{
		attron(COLOR_PAIR(9));
		mvprintw(y, x, "%02x", ARENA[i]);
		attroff(COLOR_PAIR(9));
	}
}

void			print_arena_visu(t_vm *vm)
{
	int		i;
	int		x;
	int		y;

	i = 0;
	x = 1;
	y = 1;
	while (i < MEM_SIZE)
	{
		print_arena_content(vm, i, y, x);
		x = x + 2;
		mvprintw(y, x, " ");
		x++;
		if (i && (i + 1) % 64 == 0)
		{
			y++;
			x = 1;
		}
		i++;
	}
}

void			display_winner(t_vm *vm)
{
	int	winner;

	winner = vm->last_alive->id;
	attron(COLOR_PAIR(winner + 1));
	mvprintw(40, 198, "!!!!!!!!! %s win !!!!!!!!\n",
		vm->last_alive->name);
	refresh();
	sleep(1000);
	endwin();
	curs_set(1);
	exit(0);
}
