/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   over.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabshire <gabshire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 17:33:36 by gabshire          #+#    #+#             */
/*   Updated: 2019/06/04 15:18:58 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_simup(t_format *p, size_t len, char c)
{
	while (len)
	{
		p->b_i == MAX_BUF_SIZE ? write_and_zero(p) : 0;
		p->buf[p->b_i] = c;
		++p->b_i;
		--len;
	}
}

size_t	kol_sim(unsigned long long int d, size_t base)
{
	size_t k;

	k = 0;
	if (!d)
		return (1);
	while (d)
	{
		++k;
		d /= base;
	}
	return (k);
}

void	itua_base_mod(t_format_d *d, t_format *p, size_t f)
{
	char	c;
	int		finish;

	c = !f ? 'a' : 'A';
	finish = d->len + p->b_i;
	if (finish >= MAX_BUF_SIZE)
	{
		write_and_zero(p);
		finish = d->len;
	}
	!d->o && d->len > 0 ? p->buf[p->b_i++] = '0' : 0;
	p->b_i = finish;
	while (d->o)
	{
		p->buf[--finish] = d->o % d->base < 10 ? d->o % d->base + '0' :
			d->o % d->base - 10 + c;
		d->o /= d->base;
	}
}

void	write_and_zero(t_format *p)
{
	write(1, p->buf, p->b_i);
	p->b_i = 0;
	ft_bzero(p->buf, MAX_BUF_SIZE);
}

void	ft_restor_p(t_format *p)
{
	p->hp = 0;
	p->hps = 0;
	p->t = 0;
	p->st = 0;
	p->tp = 0;
	p->m = 0;
	p->pl = 0;
	p->pr = 0;
	p->o = 0;
	p->z = 0;
}
