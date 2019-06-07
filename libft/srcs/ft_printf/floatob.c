/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floatob.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabshire <gabshire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 09:47:48 by gabshire          #+#    #+#             */
/*   Updated: 2019/06/04 15:18:58 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_sborfloat(t_format *p, t_format_d *d, int f, char *okr)
{
	int ok;

	ok = okr ? ft_strlen(okr) : 0;
	d->spase ? p->pr = 0 : 0;
	p->len += d->spase + d->zero + d->len + ok + p->pl + p->pr + f;
	!p->m ? ft_simup(p, d->spase, ' ') : 0;
	f ? ft_simup(p, 1, '-') : 0;
	p->pl ? ft_simup(p, 1, '+') : 0;
	p->pr && !d->spase ? ft_simup(p, 1, ' ') : 0;
	(d->spase > 0 || f) && p->t > 0 ? --p->t : 0;
	ft_simup(p, d->zero, '0');
	itua_base_mod(d, p, 0);
	if (okr || p->o)
	{
		ft_simup(p, 1, '.');
		++p->len;
	}
	while (ok)
	{
		ft_simup(p, 1, *okr);
		++okr;
		--ok;
	}
	p->m ? ft_simup(p, d->spase, ' ') : 0;
}

void	ft_incf(t_format *p, t_format_d *d, int f)
{
	int r;

	f ? p->pl = 0 : 0;
	p->pl || f ? p->pr = 0 : 0;
	d->len = kol_sim(d->o, 10);
	p->t > 0 ? ++p->t : 0;
	r = d->len + p->t;
	!p->t && p->o ? ++r : 0;
	f || p->pl || (p->pr && !p->pl && p->z && p->hp > r) ? ++r : 0;
	p->m ? p->z = 0 : 0;
	!p->z && p->hp > r ? d->spase = p->hp - r : 0;
	p->z && p->hp > r ? d->zero = p->hp - r : 0;
}
