/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_len.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 05:07:55 by jwillem-          #+#    #+#             */
/*   Updated: 2019/06/11 05:14:39 by jwillem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strsplit_len(char **split)
{
	size_t	len;

	len = 0;
	while (split[len])
		++len;
	return (len);
}
