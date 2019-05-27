/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 02:46:15 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/27 22:12:52 by gabshire         ###   ########.fr       */
.fr       */
=======
/*   Updated: 2019/05/27 20:47:46 by gabshire         ###   ########.fr       */
>>>>>>> fb9e556692d728112600df6146e828d5a9e9706a
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (src[i] && i < len)
	{
		dst[i] = src[i];
		i++;
	}
	while (i < len)
	{
		dst[i] = '\0';
		i++;
	}
	return (dst);
}
