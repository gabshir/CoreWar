/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabshire <gabshire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 22:42:24 by gabshire          #+#    #+#             */
/*   Updated: 2019/06/04 15:18:58 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_nt(t_format *p, t_format_d *d, double k, int f)
{
	if ((d->o + 1) % 2 == 0)
		k >= 0.5 ? ++d->o : 0;
	else
		k > 0.5 ? ++d->o : 0;
	ft_incf(p, d, f);
	ft_sborfloat(p, d, f, NULL);
}

static void	roudingd(char *str, unsigned t, double k, int i)
{
	int l;

	l = t;
	while (t > 0 && i == 1)
	{
		i = 0;
		if (((str[t - 1] + 1) % 2 == 0 && k >= 0.5) ||
		((str[t - 1] + 1) % 2 == 1 && k > 0.5))
		{
			str[t] = '0';
			str[t - 1] = str[t - 1] + 1;
			str[l] = 0;
		}
		str[t - 1] > 9 + '0' ? i = 1 : 0;
		--t;
	}
}

static void	rounding(t_format *p, t_format_d *d, double o, int f)
{
	char			okr[p->t + 1];
	unsigned		i;

	i = 0;
	ft_bzero(okr, p->t + 1);
	while (p->t)
	{
		o *= 10;
		okr[i] = (char)o + '0';
		o -= (char)o;
		++i;
		--p->t;
	}
	roudingd(okr, i, o, 1);
	if (okr[0] > '9')
	{
		++d->o;
		okr[0] -= 10;
	}
	p->t = i;
	ft_incf(p, d, f);
	ft_sborfloat(p, d, f, okr);
}

size_t		ft_float(t_format *p)
{
	double			c;
	t_format_d		d;
	int				f;
	unsigned long	*ptr;

	ft_bzero(&d, sizeof(d));
	d.base = 10;
	c = va_arg(p->arg, double);
	if (ft_nan(p, c))
		return (1);
	ptr = (unsigned long *)&c;
	f = *ptr >> 63;
	c < 0 ? c = -c : 0;
	d.o = (unsigned long int)c;
	c -= d.o;
	p->st == 0 ? p->t = 6 : 0;
	p->t < 0 ? p->t = 6 : 0;
	!p->t ? ft_nt(p, &d, c, f) : rounding(p, &d, c, f);
	return (1);
}
