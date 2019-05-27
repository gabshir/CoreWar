/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 04:38:57 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/27 22:07:11 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			n;

	if (!dst && !src)
		return (NULL);
	d = dst;
	s = (unsigned char *)src;
	n = len;
	if (s < d)
	{
		while (n-- > 0)
			d[n] = s[n];
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
