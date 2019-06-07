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

size_t		ft_nan(t_format *p, double c)
{
	char	*str;
	int		s;
	int		t;

	str = NULL;
	c != c ? str = "nan" : 0;
	NINF ? str = "-inf" : 0;
	if (INF)
		str = p->pl ? "+inf" : "inf";
	s = str ? ft_strlen(str) : 0;
	if (s > 0)
	{
		t = p->hp - s > 0 ? p->hp - s : 0;
		!p->m ? ft_simup(p, t, ' ') : 0;
		!p->m && !t && p->pr && INF ? ft_simup(p, 1, ' ') : 0;
		while (*str)
		{
			ft_simup(p, 1, *str);
			++str;
		}
		p->m ? ft_simup(p, t, ' ') : 0;
		p->len += !t ? s : p->hp;
		!p->m && !t && p->pr && INF ? ++p->len : 0;
	}
	return (str ? 1 : 0);
}

static void	ft_ntlong(t_format *p, t_format_d *d, long double k, int f)
{
	if ((d->o + 1) % 2 == 0)
		k >= 0.5 ? ++d->o : 0;
	else
		k > 0.5 ? ++d->o : 0;
	ft_incf(p, d, f);
	ft_sborfloat(p, d, f, NULL);
}

static void	roudingdlong(char *str, unsigned t, long double k, int i)
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

static void	roundinglong(t_format *p, t_format_d *d, double o, int f)
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
	roudingdlong(okr, i, o, 1);
	if (okr[0] > '9')
	{
		++d->o;
		okr[0] -= 10;
	}
	p->t = i;
	ft_incf(p, d, f);
	ft_sborfloat(p, d, f, okr);
}

size_t		ft_floatlong(t_format *p)
{
	long double			c;
	t_format_d			d;
	int					f;

	ft_bzero(&d, sizeof(d));
	d.base = 10;
	f = 0;
	c = va_arg(p->arg, long double);
	if (c < 0)
	{
		c = -c;
		f = 1;
	}
	d.o = (unsigned long int)c;
	c -= d.o;
	p->st == 0 ? p->t = 6 : 0;
	p->t < 0 ? p->t = 6 : 0;
	!p->t ? ft_ntlong(p, &d, c, f) : roundinglong(p, &d, c, f);
	return (1);
}
