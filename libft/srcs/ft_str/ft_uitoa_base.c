/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 20:48:37 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/27 22:12:52 by gabshire         ###   ########.fr       */
.fr       */
=======
/*   Updated: 2019/05/27 20:47:46 by gabshire         ###   ########.fr       */
>>>>>>> fb9e556692d728112600df6146e828d5a9e9706a
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	ft_unsllonglen(unsigned long long num, int base)
{
	size_t	i;

	i = 0;
	if (num == 0)
		return (i = 1);
	while (num)
	{
		i++;
		num /= base;
	}
	return (i);
}

char			*ft_uitoa_base(unsigned long long num, int base)
{
	char	*str;
	size_t	digits;

	digits = ft_unsllonglen(num, base);
	str = ft_strnew(digits);
	while (digits-- > 0)
	{
		if (num % base < 10)
			str[digits] = num % base + '0';
		else
			str[digits] = num % base + 87;
		num /= base;
	}
	return (str);
}
