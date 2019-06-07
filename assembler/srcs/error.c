/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eror.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 19:55:57 by gabshire          #+#    #+#             */
/*   Updated: 2019/06/04 15:18:58 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_error(t_all *all, int er)
{
	!all ?  ft_printf("error makros \n") : 0;
	er == 0 ? ft_printf("clean file\n") : 0;
	er == 1 ? ft_printf("stroka %d stolbec %d syntax error\n", all->st, all->i) : 0;
	ft_printf("%s\n", all->line);
	exit(1);
}