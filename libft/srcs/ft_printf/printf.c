/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabshire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 09:30:13 by gabshire          #+#    #+#             */
/*   Updated: 2019/06/04 15:18:58 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_format(t_format *p)
{
	ft_flag(p);
	ft_hirina(p);
	ft_hirina(p);
	ft_tochnost(p);
	ft_tochnost(p);
	ft_flag(p);
	ft_specr(p);
	ft_flag(p);
	p->tp = *p->str;
	if (p->tp)
		ft_start(p) ? ++p->str : 0;
	ft_restor_p(p);
}

static	void	ft_cheakp(t_format *p)
{
	int k;

	k = 0;
	while (*p->str && *p->str == '%')
	{
		++p->str;
		++k;
	}
	if (k % 2 == 0)
	{
		k /= 2;
		p->len += k;
		ft_simup(p, k, '%');
		return ;
	}
	k = (k - 1) / 2;
	ft_simup(p, k, '%');
	p->len += k;
	ft_format(p);
}

static void		ft_symvoly(t_format *p)
{
	while (*p->str && *p->str != '%')
	{
		p->b_i == MAX_BUF_SIZE ? write_and_zero(p) : 0;
		p->buf[p->b_i] = *p->str;
		++p->str;
		++p->b_i;
		++p->len;
	}
}

int				ft_printf(char const *s, ...)
{
	t_format p;

	ft_bzero(&p, sizeof(p));
	p.str = (char *)s;
	va_start(p.arg, s);
	while (*p.str)
	{
		ft_symvoly(&p);
		ft_cheakp(&p);
	}
	write(1, p.buf, p.b_i);
	va_end(p.arg);
	return (p.len);
}
