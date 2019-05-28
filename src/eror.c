/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eror.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabshire <gabshire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 19:55:57 by gabshire          #+#    #+#             */
/*   Updated: 2019/05/27 20:11:35 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "op.h"

void	ft_eroror(int er)
{
	er == 0 ? ft_printf("clean file\n") : 0;
	er == 1 ? ft_printf("syntax error\n") : 0;
	exit(1);
}