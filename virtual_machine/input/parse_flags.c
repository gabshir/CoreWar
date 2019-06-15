/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlabadie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 20:37:01 by dlabadie          #+#    #+#             */
/*   Updated: 2019/06/14 20:37:03 by dlabadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		parse_visu(t_parser *parser, t_vm *vm)
{
	vm->visu = true;
	init_visu(vm);
	(parser->index) -= 1;
	(parser->arg) += 1;
}

void		parse_aff(t_parser *parser, t_vm *vm)
{
	vm->aff = true;
	(parser->index) -= 1;
	(parser->arg) += 1;
}

void		parse_live(t_parser *parser, t_vm *vm)
{
	vm->live = true;
	(parser->index) -= 1;
	(parser->arg) += 1;
}
