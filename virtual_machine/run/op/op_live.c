/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 18:12:43 by dlabadie          #+#    #+#             */
/*   Updated: 2019/06/14 23:33:57 by jwillem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void				op_live(t_vm *vm, t_cursor *cursor)
{
	int			player_id;
	t_player	*player;

	cursor->step += OP_CODE_LEN;
	if (cursor->args_types[FIRST] & (T_REG | T_DIR | T_IND))
		player_id = g_gets[cursor->args_types[FIRST] / 2].get(vm, cursor);
	else
		player_id = 0;
	vm->lives_num++;
	cursor->last_live = vm->cycles;
	player = NULL;
	if (player_id <= -1 && player_id >= -(vm->players_num))
	{
		player = vm->players[INDEX(FT_ABS(player_id))];
		player->last_live = vm->cycles;
		player->current_lives_num++;
		vm->last_alive = player;
		if (vm->live)
			ft_printf("A process shows that player %s is alive\n", \
				vm->players[INDEX(FT_ABS(player_id))]->name);
	}
}
