/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabshire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 16:54:19 by gabshire          #+#    #+#             */
/*   Updated: 2019/06/04 15:18:58 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	ft_specrl(t_format *p)
{
	size_t f;

	f = 0;
	if (*p->str == 'l')
	{
		++p->str;
		++f;
		p->sr[0] = 'l';
		if (*p->str && *p->str == 'l')
		{
			++p->str;
			p->sr[1] = 'l';
		}
	}
	return (f);
}

static size_t	ft_specrh(t_format *p)
{
	size_t f;

	f = 0;
	if (*p->str == 'h')
	{
		++p->str;
		++f;
		p->sr[0] = 'h';
		if (*p->str && *p->str == 'h')
		{
			++p->str;
			p->sr[1] = 'h';
		}
	}
	return (f);
}

static size_t	ft_specrjzl(t_format *p)
{
	if (*p->str == 'j' || *p->str == 'z' || *p->str == 't' || *p->str == 'L')
	{
		p->sr[0] = *p->str == 'z' ? 'j' : *p->str;
		++p->str;
		return (1);
	}
	return (0);
}

void			ft_specr(t_format *p)
{
	if (!ft_specrl(p))
		if (!ft_specrh(p))
			ft_specrjzl(p);
}

size_t			ft_start(t_format *p)
{
	if (p->tp == 'c' && p->sr[0] != 'l')
		return (ft_char(p));
	if (p->tp == 'C' || (p->tp == 'c' && p->sr[0] != 'l'))
		return (ft_charu(p, va_arg(p->arg, wint_t)));
	if (p->tp == 's')
		return (ft_printstr(p));
	if (p->tp == 'S')
		return (ft_printstru(p));
	if (p->tp == 'd' || p->tp == 'i' || p->tp == 'D')
		return (ft_flag_d_i(p));
	if (p->tp == 'u' || p->tp == 'U')
		return (ft_flag_u(p));
	if (p->tp == 'x' || p->tp == 'X' || p->tp == 'p'
	|| p->tp == 'o' || p->tp == 'O')
		return (ft_flag_x(p));
	if ((p->tp == 'f' || p->tp == 'F') && p->sr[0] != 'L')
		return (ft_float(p));
	if (p->tp == 'f' && p->sr[0] == 'L')
		return (ft_floatlong(p));
	return (0);
}
