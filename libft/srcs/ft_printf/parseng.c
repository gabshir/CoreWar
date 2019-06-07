/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseng.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabshire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 16:54:30 by gabshire          #+#    #+#             */
/*   Updated: 2019/06/04 15:18:58 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_bonus(t_format *p, int f)
{
	int s;

	++p->str;
	s = va_arg(p->arg, int);
	if (!f)
	{
		if (s < 0)
			return ;
		p->t = s;
		p->st = 1;
		return ;
	}
	if (s < 0)
	{
		s = -s;
		p->m = 1;
	}
	p->hp = s;
	p->hps = 1;
}

void		ft_hirina(t_format *p)
{
	int		s;
	char	*str;

	str = p->str;
	if (p->str && *p->str == '*')
		return (ft_bonus(p, 1));
	s = 0;
	while (p->str && *p->str >= '0' && *p->str <= '9')
	{
		s = s * 10 + *p->str - '0';
		++p->str;
	}
	if (str != p->str)
	{
		p->hps = 1;
		p->hp = s;
	}
}

void		ft_tochnost(t_format *p)
{
	int		s;
	char	*str;

	s = 0;
	str = p->str;
	p->str && *p->str == '.' ? ++p->str : 0;
	if (p->str && *p->str == '*')
		return (ft_bonus(p, 0));
	while (p->str && *p->str == '-')
	{
		++p->str;
		p->m = 1;
	}
	while (p->str && *p->str >= '0' && *p->str <= '9')
	{
		s = s * 10 + *p->str - '0';
		++p->str;
	}
	if (str != p->str)
	{
		p->st = 1;
		p->t = s;
	}
}

void		ft_flag(t_format *p)
{
	while (p->str && (*p->str == '-' || *p->str == '+'
	|| *p->str == ' ' || *p->str == '#' || *p->str == '0'))
	{
		if (*p->str == '-')
			p->m = 1;
		else if (*p->str == '+')
			p->pl = 1;
		else if (*p->str == ' ')
			p->pr = 1;
		else if (*p->str == '#')
			p->o = 1;
		else if (*p->str == '0')
			p->z = 1;
		++p->str;
	}
}
