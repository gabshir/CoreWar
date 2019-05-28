/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 17:05:01 by wballaba          #+#    #+#             */
/*   Updated: 2019/05/27 22:23:49 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_sqrt(int nb)
{
	int i;
	int sqr;

	i = 1;
	sqr = 1;
	if (nb > 0)
	{
		while (sqr <= nb)
		{
			sqr = i * i;
			if (sqr == nb)
				return (i);
			i++;
		}
	}
	return (0);
}
