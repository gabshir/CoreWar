/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabshire <gabshire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 00:29:36 by gabshire          #+#    #+#             */
/*   Updated: 2019/06/09 22:08:44 by gabshire         ###   ########.fr       */
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

int 		transform(unsigned int a)
{
	char *temp;
	unsigned l;
	int r;

	l = 2;
	temp = ft_strnew(2);
	while(a)
	{
		temp[--l] = a % 16 < 10 ? a % 16 + '0' : a % 16 + 'a' - 10;
		a /= 16;
	}
	r = ft_atoi_base(temp, 16);
	free(temp);
	return (r);
}

char			*name_and_comment(char *str, int f)
{
	char	*v;
	unsigned r;
	unsigned	k;

	r = f == 0 ? PROG_NAME_LENGTH : COMMENT_LENGTH;
	v = ft_memalloc(r);
	k = 0;
	while(*str)
	{
		v[k] = transform(*str);
		++str;
		++k;
	}
	return (v);
}

void		assembler(t_all *all)
{
	t_list	*temp;

//	temp = ft_lstnew(NULL, 0);
//	temp->content = magik(all->magic);
//	ft_lstpush(&all->source, temp);
	char test[5];

	write(1, test, 3);
	temp = ft_lstnew(NULL, 0);
	temp->content = name_and_comment(all->prog_name, 0);
	ft_lstpush(&all->source, temp);
}