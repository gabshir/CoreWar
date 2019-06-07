/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printtnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabshire <gabshire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 17:41:43 by gabshire          #+#    #+#             */
/*   Updated: 2019/06/04 15:18:58 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_printnbru(t_format *p, unsigned long long k)
{
	t_format_d	d;
	int			f;

	f = 0;
	ft_bzero(&d, sizeof(d));
	d.o = k;
	d.len = incd(p, kol_sim(d.o, 10), f, d.o);
	d.base = 10;
	ft_format_d(p, &d, f);
	return (1);
}

size_t	ft_printnbr(t_format *p, long long k)
{
	t_format_d	d;
	int			f;

	f = 0;
	ft_bzero(&d, sizeof(d));
	if (k < 0)
	{
		d.o = -k;
		f = 1;
		p->pr = 0;
	}
	else
		d.o = k;
	d.len = incd(p, kol_sim(d.o, 10), f, d.o);
	d.base = 10;
	ft_format_d(p, &d, f);
	return (1);
}
