/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 04:23:39 by jwillem-          #+#    #+#             */
/*   Updated: 2019/06/15 03:00:42 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	quick_pass(t_all *all)
{
	while (SPLIT[all->i] && (SPLIT[all->i] == ' ' || SPLIT[all->i] == '\t'))
		++all->i;
}

int		checkform(t_all *all)
{
	while (all->split[all->st + 1])
	{
		++all->st;
		all->i = 0;
		while (SPLIT[all->i])
		{
			if (SPLIT[all->i] == COMMENT_CHAR ||
				SPLIT[all->i] == ALT_COMMENT_CHAR || SPLIT[all->i] == '\n')
				break ;
			if (SPLIT[all->i] == ' ' || SPLIT[all->i] == '\t')
				all->i++;
			else
				return (1);
		}
	}
	return (0);
}

int		last_check(t_all *all)
{
	char	c;
	char	ac;

	c = COMMENT_CHAR;
	ac = ALT_COMMENT_CHAR;
	while (SPLIT[all->i])
	{
		if (SPLIT[all->i] == ' ' || SPLIT[all->i] == '\t' ||
			SPLIT[all->i] == '\n')
			++all->i;
		else if (SPLIT[all->i] == c || SPLIT[all->i] == ac)
			break ;
		else
			return (1);
	}
	all->i = 0;
	return (0);
}
