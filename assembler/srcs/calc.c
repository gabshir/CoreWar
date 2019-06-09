/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabshire <gabshire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 00:29:36 by gabshire          #+#    #+#             */
/*   Updated: 2019/06/09 22:12:00 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

//char			*magik(unsigned int c)
//{
//	char		*v;
//	unsigned	l;
//
//	v = ft_memalloc(5);
//	l = 4;
//	while (c)
//	{
//		v[--l] = c % 16 > 10 ? c % 16 + 'a' - 10 :  c % 16 - 10 + '0';
//		c /= 16;
//	}
//	return (v);
//}


void		assembler(t_all *all)
{
	t_list	*temp;

//	temp = ft_lstnew(NULL, 0);
//	temp->content = magik(all->magic);
//	ft_lstpush(&all->source, temp);
	char test[5];

	write(1, test, 3);
	temp = ft_lstnew(NULL, 0);
	ft_lstpush(&all->source, temp);
}