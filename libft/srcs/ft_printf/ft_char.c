/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabshire <gabshire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 13:54:20 by gabshire          #+#    #+#             */
/*   Updated: 2019/06/04 15:18:58 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_printcharm(t_format *mod, char c)
{
	mod->b_i == MAX_BUF_SIZE ? write_and_zero(mod) : 0;
	mod->buf[mod->b_i] = c;
	++mod->b_i;
	if (mod->hp < 2)
	{
		++mod->len;
		return ;
	}
	mod->len += mod->hp;
	--mod->hp;
	mod->z ? ft_simup(mod, mod->hp, '0') : ft_simup(mod, mod->hp, ' ');
}

static void	ft_printcharmnull(t_format *mod, char c)
{
	if (mod->hp < 2)
	{
		mod->b_i == MAX_BUF_SIZE ? write_and_zero(mod) : 0;
		mod->buf[mod->b_i] = c;
		++mod->b_i;
		++mod->len;
		return ;
	}
	mod->len += mod->hp;
	--mod->hp;
	mod->z ? ft_simup(mod, mod->hp, '0') : ft_simup(mod, mod->hp, ' ');
	mod->b_i == MAX_BUF_SIZE ? write_and_zero(mod) : 0;
	mod->buf[mod->b_i] = c;
	++mod->b_i;
}

size_t		ft_char(t_format *p)
{
	char	c;

	c = va_arg(p->arg, int);
	p->m == 1 ? ft_printcharm(p, c) : ft_printcharmnull(p, c);
	return (1);
}
