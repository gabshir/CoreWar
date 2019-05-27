/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 04:58:47 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/27 22:12:52 by gabshire         ###   ########.fr       */
.fr       */
=======
/*   Updated: 2019/05/27 20:47:46 by gabshire         ###   ########.fr       */
>>>>>>> fb9e556692d728112600df6146e828d5a9e9706a
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((const unsigned char)s1[i] - (const unsigned char)s2[i]);
		i++;
	}
	if (s1[i] != s2[i])
		return ((const unsigned char)s1[i] - (const unsigned char)s2[i]);
	return (0);
}
