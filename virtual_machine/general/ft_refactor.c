/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_refactor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlabadie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 18:04:29 by dlabadie          #+#    #+#             */
/*   Updated: 2019/06/10 18:04:31 by dlabadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int		strnumlen(const char *str, int i)
{
	int		ln;

	ln = i;
	while (str[ln] <= '9' && str[ln] >= '0')
		ln++;
	return (ln - i);
}

static int		detectlongstr(const char *str, int i, int sign)
{
	int		ln;

	ln = strnumlen(str, i);
	if (sign)
	{
		if (ln > 19 || (ln == 19 && (ft_strcmp(str + i,
			"9223372036854775808") > 0)))
			return (-1);
	}
	else
	{
		if (ln > 19 || (ln == 19 && (ft_strcmp(str + i,
			"9223372036854775807") > 0)))
			return (-1);
	}
	return (1);
}

int				cat_atoi(const char *str)
{
	int				i;
	int				sign;
	long int		res;
	int				flag;

	sign = 0;
	i = 0;
	flag = detectlongstr(str, i, sign);
	if (flag != 1)
		return (flag);
	res = 0;
	while (str[i])
	{
		if (!(str[i] <= '9' && str[i] >= '0'))
			return (-1);
		else
			res = res * 10 + (str[i] - '0');
		i++;
	}
	return ((int)res);
}
