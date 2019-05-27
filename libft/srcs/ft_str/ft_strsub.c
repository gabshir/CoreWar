/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 14:39:10 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/27 22:12:52 by gabshire         ###   ########.fr       */
.fr       */
=======
/*   Updated: 2019/05/27 20:47:46 by gabshire         ###   ########.fr       */
>>>>>>> fb9e556692d728112600df6146e828d5a9e9706a
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		return (NULL);
	if (!(substr = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (s && i < len)
	{
		substr[i] = s[start];
		i++;
		start++;
	}
	substr[i] = '\0';
	return (substr);
}
