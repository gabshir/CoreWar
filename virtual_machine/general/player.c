/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlabadie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 17:50:40 by dlabadie          #+#    #+#             */
/*   Updated: 2019/06/05 17:50:42 by dlabadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_player		*init_player(int id)
{
	t_player *player;

	if (!(player = (t_player *)ft_memalloc(sizeof(t_player))))
		print_error(MALLOC);
	player->id = id;
	player->name = NULL;
	player->comment = NULL;
	player->code_size = 0;
	player->code = NULL;
	player->last_live = 0;
	player->current_lives_num = 0;
	player->previous_lives_num = 0;
	player->next = NULL;
	return (player);
}

void			add_player(t_player **list, t_player *new)
{
	t_player *current;

	if (list && new)
	{
		if (*list)
		{
			current = *list;
			while (current->next)
				current = current->next;
			current->next = new;
		}
		else
			*list = new;
	}
}

t_player		*get_player(t_player *list, int id)
{
	t_player *player;

	player = NULL;
	if (id >= 1 && id <= MAX_PLAYERS)
	{
		player = list;
		while (player)
		{
			if (player->id == id)
				return (player);
			player = player->next;
		}
	}
	return (player);
}

static void		update_players_ids(t_player *list)
{
	t_player	*player;
	int			id;

	id = 1;
	player = list;
	while (player)
	{
		if (player->id == 0)
		{
			while (get_player(list, id))
				id++;
			player->id = id;
		}
		player = player->next;
	}
}

void			reload_players_list(t_vm *vm, t_player *player)
{
	int id;

	id = 1;
	update_players_ids(player);
	while (id <= vm->players_num)
	{
		if (!(vm->players[INDEX(id)] = get_player(player, id)))
			print_usage();
		id++;
	}
	vm->last_alive = vm->players[INDEX(vm->players_num)];
}
