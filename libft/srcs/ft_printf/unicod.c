/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unicod.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabshire <gabshire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 14:06:56 by gabshire          #+#    #+#             */
/*   Updated: 2019/06/04 15:18:58 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		oct_4(wint_t c, t_format *p)
{
	p->len += 4;
	p->b_i + 4 >= MAX_BUF_SIZE ? write_and_zero(p) : 0;
	p->buf[p->b_i] = (c >> 18) + 240;
	p->buf[++p->b_i] = ((c >> 12) & 63) + 128;
	p->buf[++p->b_i] = ((c >> 6) & 63) + 128;
	p->buf[++p->b_i] = ((c & 63) + 128);
	++p->b_i;
}

static void		oct_3(wint_t c, t_format *p)
{
	p->len += 3;
	p->b_i + 3 >= MAX_BUF_SIZE ? write_and_zero(p) : 0;
	p->buf[p->b_i] = (c >> 12) + 224;
	p->buf[++p->b_i] = ((c >> 6) & 63) + 128;
	p->buf[++p->b_i] = ((c & 63) + 128);
	++p->b_i;
}

static void		oct_2(wint_t c, t_format *p)
{
	p->len += 2;
	p->b_i + 2 >= MAX_BUF_SIZE ? write_and_zero(p) : 0;
	p->buf[p->b_i] = (c >> 6) + 192;
	p->buf[++p->b_i] = ((c & 63) + 128);
	++p->b_i;
}

static void		oct_1(wint_t c, t_format *p)
{
	++p->len;
	p->b_i + 1 >= MAX_BUF_SIZE ? write_and_zero(p) : 0;
	p->buf[p->b_i] = c;
	++p->b_i;
}

size_t			ft_charu(t_format *p, wint_t c)
{
	if (c <= 127)
		oct_1(c, p);
	else if (c >= 127 && c <= 2047)
		oct_2(c, p);
	else if (c >= 2048 && c <= 65535)
		oct_3(c, p);
	else if (c >= 65536 && c <= 2097151)
		oct_4(c, p);
	return (1);
}
