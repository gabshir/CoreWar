/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flagidiux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabshire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 16:54:52 by gabshire          #+#    #+#             */
/*   Updated: 2019/06/04 15:18:58 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_flag_d_i(t_format *p)
{
	if (p->tp == 'D')
		return (ft_printnbr(p, va_arg(p->arg, long long int)));
	else if (!p->sr[0])
		return (ft_printnbr(p, va_arg(p->arg, int)));
	else if ((p->sr[0] == 'l' && p->sr[1] == 'l') || p->sr[0] == 'j')
		return (ft_printnbr(p, va_arg(p->arg, long long int)));
	else if (p->sr[0] == 'l' && !p->sr[1])
		return (ft_printnbr(p, va_arg(p->arg, long int)));
	else if (p->sr[0] == 'h' && p->sr[1] == 'h')
		return (ft_printnbr(p, (char)va_arg(p->arg, unsigned int)));
	else if (p->sr[0] == 'h' && !p->sr[1])
		return (ft_printnbr(p, (short)va_arg(p->arg, int)));
	return (0);
}

size_t	ft_flag_u(t_format *p)
{
	if (p->tp == 'U')
		return (ft_printnbru(p, va_arg(p->arg, unsigned long int)));
	else if (!p->sr[0])
		return (ft_printnbru(p, va_arg(p->arg, unsigned int)));
	else if ((p->sr[0] == 'l' && p->sr[1] == 'l') || p->sr[0] == 'j')
		return (ft_printnbru(p, va_arg(p->arg, unsigned long long int)));
	else if (p->sr[0] == 'l' && !p->sr[1])
		return (ft_printnbru(p, va_arg(p->arg, unsigned long int)));
	else if (p->sr[0] == 'h' && p->sr[1] == 'h')
		return (ft_printnbru(p, (unsigned char)va_arg(p->arg, int)));
	else if (p->sr[0] == 'h' && !p->sr[1])
		return (ft_printnbru(p, (unsigned short)va_arg(p->arg, int)));
	return (0);
}

size_t	ft_flag_x(t_format *p)
{
	int	f;

	f = p->tp != 'p' && p->tp != 'x' && p->tp != 'o';
	if (p->tp == 'O')
		return (ft_printx(p, va_arg(p->arg, long long int), f));
	else if (p->tp == 'p')
		return (ft_printx(p, va_arg(p->arg, unsigned long long int), f));
	else if (!p->sr[0])
		return (ft_printx(p, va_arg(p->arg, unsigned int), f));
	else if ((p->sr[0] == 'l' && p->sr[1] == 'l') || p->sr[0] == 'j')
		return (ft_printx(p, va_arg(p->arg, long long int), f));
	else if (p->sr[0] == 'l' && !p->sr[1])
		return (ft_printx(p, va_arg(p->arg, long int), f));
	else if (p->sr[0] == 'h' && !p->sr[1])
		return (ft_printx(p, (unsigned short)va_arg(p->arg, int), f));
	else if (p->sr[0] == 'h' && p->sr[1] == 'h')
		return (ft_printx(p, (unsigned char)va_arg(p->arg, int), f));
	return (0);
}
