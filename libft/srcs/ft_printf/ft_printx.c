/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabshire <gabshire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 19:04:32 by gabshire          #+#    #+#             */
/*   Updated: 2019/06/04 15:18:58 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_napolnenie_x(t_format *p, t_format_d *d, int f)
{
	!p->m ? ft_simup(p, d->spase, ' ') : 0;
	if (p->o)
	{
		ft_simup(p, 1, '0');
		if (p->tp != 'o' && p->tp != 'O')
			!f ? ft_simup(p, 1, 'x') : ft_simup(p, 1, 'X');
	}
	ft_simup(p, d->zero, '0');
	itua_base_mod(d, p, f);
	p->m ? ft_simup(p, d->spase, ' ') : 0;
}

static void		ft_formatx(t_format *p, t_format_d *d, int f)
{
	d->rd = d->len + d->zero + d->spase;
	if (p->o)
		d->rd += p->tp == 'O' || p->tp == 'o' ? 1 : 2;
	p->len += d->rd;
	ft_napolnenie_x(p, d, f);
}

static size_t	kol_spasex(t_format *p, t_format_d *d)
{
	unsigned char f;

	f = p->tp == 'o' || p->tp == 'O' ? 1 : 2;
	if (!p->o && !d->zero && p->hp > d->len)
		return (p->hp - d->len);
	if (p->o && !d->zero && p->hp > d->len + f)
		return (p->hp - d->len - f);
	if (!p->o && p->hp > d->len && p->hp > p->t)
		return (d->len > p->t ? p->hp - d->len : p->hp - p->t);
	if (p->o && p->hp > d->len + f && p->hp > p->t + f)
		return (d->len > p->t ? p->hp - d->len - f : p->hp - p->t - f);
	return (0);
}

static size_t	incx(t_format *p, t_format_d *d)
{
	unsigned char f;

	f = p->tp == 'O' || p->tp == 'o' ? 1 : 2;
	p->tp == 'p' ? p->o = 1 : 0;
	(p->tp == 'O' || p->tp == 'o') && !p->st && !d->o ? p->o = 0 : 0;
	if (!p->z)
		return (d->o == 0 && p->st && !p->t ? 0 : d->len);
	p->m && p->hp > d->len && p->z ? p->m = 1 : 0;
	p->hp > d->len && !p->st && !p->o && !p->m ? p->t = p->hp : 0;
	p->hp > d->len && !p->st && p->o && !p->m ? p->t = p->hp - f : 0;
	return (!d->o && p->st && !p->t ? 0 : d->len);
}

size_t			ft_printx(t_format *p, unsigned long long int k, int f)
{
	t_format_d	d;

	ft_bzero(&d, sizeof(d));
	!k && p->tp != 'o' && p->tp != 'O' ? p->o = 0 : 0;
	d.base = p->tp == 'O' || p->tp == 'o' ? 8 : 16;
	d.o = k;
	d.len = kol_sim(k, d.base);
	d.len = incx(p, &d);
	p->t > d.len ? d.zero = p->t - d.len : 0;
	(p->tp == 'o' || p->tp == 'O') && p->st && d.zero > 0 && p->o ? --p->o : 0;
	d.spase = kol_spasex(p, &d);
	ft_formatx(p, &d, f);
	return (1);
}
