/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 17:25:04 by dlabadie          #+#    #+#             */
/*   Updated: 2019/06/14 22:33:43 by jwillem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		parse_n_flag(t_parser *parser, t_vm *vm)
{
	int id;

	id = 0;
	if (parser->index >= 3)
	{
		if ((id = cat_atoi(*(parser->arg + 1))) < 1)
			print_usage();
		else if (id > MAX_PLAYERS)
			print_usage();
		else if (get_player(parser->player, id))
			print_usage();
		else if (ft_strlen(*(parser->arg + 2)) < 4)
			print_usage();
		else if (ft_strcmp(ft_strchr(*(parser->arg + 2), '\0') - \
		ft_strlen(".cor"), ".cor"))
			print_usage();
		add_player(&(parser->player), parse_cor_file(*(parser->arg + 2), id));
		vm->players_num++;
		(parser->index) -= 3;
		(parser->arg) += 3;
	}
	else
		print_usage();
}

static void		parse_file(t_parser *parser, t_vm *vm)
{
	if (ft_strlen(*(parser->arg)) >= 4 && \
	!ft_strcmp(ft_strchr(*(parser->arg), '\0') - ft_strlen(".cor"), ".cor"))
	{
		add_player(&(parser->player), parse_cor_file(*(parser->arg), 0));
		vm->players_num++;
		(parser->index)--;
		(parser->arg)++;
	}
	else
		print_usage();
}

static void		parse_dump_flag(t_parser *parser, t_vm *vm)
{
	if (!vm->dump_print_mode && \
	parser->index >= 2 && cat_atoi(*(parser->arg + 1)) != -1)
	{
		if ((vm->dump_cycle = ft_atoi(*(parser->arg + 1))) < 0)
			vm->dump_cycle = -1;
		vm->dump_print_mode = 32;
		(parser->index) -= 2;
		(parser->arg) += 2;
	}
	else
		print_usage();
}

void			parse_flags(t_parser *parser, t_vm *vm)
{
	if (!ft_strcmp(*(parser->arg), "-dump"))
		parse_dump_flag(parser, vm);
	else if (!ft_strcmp(*(parser->arg), "-n"))
		parse_n_flag(parser, vm);
	else if (!ft_strcmp(*(parser->arg), "-visu"))
		parse_visu(parser, vm);
	else if (!ft_strcmp(*(parser->arg), "-aff"))
		parse_aff(parser, vm);
	else if (!ft_strcmp(*(parser->arg), "-live"))
		parse_live(parser, vm);
	else
		parse_file(parser, vm);
}
