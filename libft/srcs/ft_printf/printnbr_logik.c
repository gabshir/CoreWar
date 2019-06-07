/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabshire <gabshire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 21:43:47 by gabshire          #+#    #+#             */
/*   Updated: 2019/06/04 15:18:58 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	ft_kol_spase(t_format *mod, int len, int f, size_t zero)
{
	if (!f && !mod->pl && !zero && mod->hp > len)
		return (mod->hp - len);
	if ((f || mod->pl) && !zero && mod->hp > len + 1)
		return (--mod->hp - len);
	if (!f && !mod->pl && mod->hp > len && mod->hp > mod->t)
		return (len > mod->t ? mod->hp - len : mod->hp - mod->t);
	if ((f || mod->pl) && mod->hp > len + 1 && mod->hp > mod->t + 1)
		return (len > mod->t ? --mod->hp - len : --mod->hp - mod->t);
	return (0);
}

static void		ft_napolnenie_dm(int f, t_format *p, t_format_d *d)
{
	p->pr && !p->pl ? ft_simup(p, 1, ' ') : 0;
	if (f || (p->pl && p->tp != 'u'))
		f ? ft_simup(p, 1, '-') : ft_simup(p, 1, '+');
	ft_simup(p, d->zero, '0');
	itua_base_mod(d, p, 0);
	ft_simup(p, d->spase, ' ');
}

static void		ft_napolnenie_d(int f, t_format *p, t_format_d *d)
{
	if (p->pr && !d->spase && !f && !p->pl && p->tp != 'u')
		ft_simup(p, 1, ' ');
	else if (d->spase > 0)
		ft_simup(p, d->spase, ' ');
	if (f || (p->pl && p->tp != 'u'))
		f ? ft_simup(p, 1, '-') : ft_simup(p, 1, '+');
	ft_simup(p, d->zero, '0');
	itua_base_mod(d, p, 0);
}

void			ft_format_d(t_format *p, t_format_d *d, int f)
{
	d->zero = p->t > d->len ? p->t - d->len : 0;
	d->spase = ft_kol_spase(p, d->len, f, d->zero);
	f ? d->minus = 1 : 0;
	!d->minus && p->pl && p->tp != 'u' ? d->plus = 1 : 0;
	d->rd = d->len + d->zero + d->spase + d->minus + d->plus;
	if (p->pr && p->m && p->tp != 'u' && !p->pl)
		++d->rd;
	else if (p->pr && !p->m && !d->spase && p->tp != 'u' &&
		!f && !p->pl && p->tp != 'u')
		++d->rd;
	p->len += d->rd;
	p->m ? ft_napolnenie_dm(f, p, d) : ft_napolnenie_d(f, p, d);
}

size_t			incd(t_format *mod, int len, int f, size_t n)
{
	mod->m && mod->pr && !mod->z && mod->hp > 0 ? --mod->hp : 0;
	if (!mod->z)
		return (!n && mod->st && !mod->t ? 0 : len);
	mod->m && mod->hp > len ? mod->m = 1 : 0;
	mod->hp > len && !mod->st && !f && !mod->pl
		&& !mod->pr && !mod->m ? mod->t = mod->hp : 0;
	mod->hp > len && !mod->st && !f && !mod->pl
		&& mod->pr && mod->hp > 0 ? mod->t = --mod->hp : 0;
	mod->hp > len && mod->st == 0 && !mod->m
		&& (f || mod->pl) ? mod->t = --mod->hp : 0;
	return (!n && mod->st && !mod->t ? 0 : len);
}
