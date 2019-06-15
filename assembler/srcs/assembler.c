/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:37:16 by gabshire          #+#    #+#             */
/*   Updated: 2019/06/15 02:59:55 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	check_cmd_correctness(t_all *all, size_t i, unsigned length)
{
	i == length && SPLIT[all->i] != '"' ?
	ft_error(all, Semantic, CMD_size_exceeded) : ++all->i;
	last_check(all) ? ft_error(all, Syntactic, Wrong_argument) : 0;
}

static void	checkname(t_all *all, int f)
{
	size_t		i;
	unsigned	length;

	i = 0;
	length = f == 0 ? PROG_NAME_LENGTH : COMMENT_LENGTH;
	quick_pass(all);
	if (SPLIT[all->i] && SPLIT[all->i] != '"')
	{
		ft_error(all, Syntactic, Wrong_argument);
		return ;
	}
	++all->i;
	while (i < length && SPLIT && SPLIT[all->i] != '"')
	{
		f == 0 ? all->prog_name[i] = SPLIT[all->i] : 0;
		f == 1 ? all->comment[i] = SPLIT[all->i] : 0;
		++i;
		++all->i;
		if (!SPLIT[all->i])
		{
			all->i = 0;
			++all->st;
		}
	}
	check_cmd_correctness(all, i, length);
}

static int	check_name_and_comment(t_all *all, int f)
{
	unsigned	i;
	unsigned	j;
	char		*str;

	i = 0;
	j = all->i;
	str = f == 0 ? NAME_CMD_STRING : COMMENT_CMD_STRING;
	while (str[i])
	{
		if (SPLIT[all->i] == str[i])
		{
			++i;
			++all->i;
		}
		else
			break ;
	}
	if (!str[i])
		return (1);
	all->i = j;
	return (0);
}

void		readfile(t_all *all, char *file_name)
{
	char	flags[2];

	ft_bzero(&flags, 2);
	all->magic = COREWAR_EXEC_MAGIC;
	while (!flags[0] || !flags[1])
	{
		checkform(all);
		!SPLIT ? ft_error(all, Semantic, Bad_CMD_declaration) : 0;
		if (check_name_and_comment(all, 0) && !flags[0])
		{
			flags[0] = 1;
			checkname(all, 0);
		}
		else if (check_name_and_comment(all, 1) && !flags[1])
		{
			flags[1] = 1;
			checkname(all, 1);
		}
		else
		{
			ft_error(all, Semantic, Bad_CMD_declaration);
			print_errors(all, file_name);
		}
	}
}
