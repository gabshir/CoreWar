/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unicod_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:19:35 by gabshire          #+#    #+#             */
/*   Updated: 2019/06/04 15:18:58 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	ft_strlenu(const wchar_t *str)
{
	size_t i;

	i = 0;
	while (str[i])
		++i;
	return (i);
}

static void		ft_nap_stru(const wchar_t *start, int len, t_format *p)
{
	int	j;

	j = 0;
	start == NULL ? start = (L"(null)") : 0;
	while (len)
	{
		ft_charu(p, start[j]);
		--len;
		++j;
	}
}

size_t			ft_printstru(t_format *p)
{
	wchar_t	*start;
	int		len;

	start = va_arg(p->arg, wchar_t*);
	len = start == NULL ? 6 : ft_strlenu(start);
	len > p->t && p->st ? len = p->t : 0;
	p->m ? ft_nap_stru(start, ft_strlenu(start), p) : 0;
	if (len < p->hp)
	{
		p->hp -= len;
		!p->z ? ft_simup(p, p->hp, ' ') : ft_simup(p, p->hp, '0');
		p->len += p->hp;
	}
	!p->m ? ft_nap_stru(start, len, p) : 0;
	return (1);
}
