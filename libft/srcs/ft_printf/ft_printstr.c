/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabshire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 09:28:40 by gabshire          #+#    #+#             */
/*   Updated: 2019/06/04 15:18:58 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_nap_str(const char *start, int len, t_format *p)
{
	int	j;

	j = 0;
	start == NULL ? start = "(null)" : 0;
	p->len += len;
	while (len)
	{
		p->b_i == MAX_BUF_SIZE ? write_and_zero(p) : 0;
		p->buf[p->b_i] = start[j];
		++p->b_i;
		--len;
		++j;
	}
}

size_t		ft_printstr(t_format *p)
{
	char	*start;
	int		len;

	start = va_arg(p->arg, char*);
	len = start == NULL ? 6 : ft_strlen(start);
	len > p->t && p->st ? len = p->t : 0;
	p->m ? ft_nap_str(start, len, p) : 0;
	if (len < p->hp)
	{
		p->hp -= len;
		!p->z ? ft_simup(p, p->hp, ' ') : ft_simup(p, p->hp, '0');
		p->len += p->hp;
	}
	!p->m ? ft_nap_str(start, len, p) : 0;
	return (1);
}
