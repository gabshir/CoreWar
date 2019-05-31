/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:37:16 by gabshire          #+#    #+#             */
/*   Updated: 2019/05/31 15:53:20 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	quick_pass(t_all *all)
{
	while(all->line[all->i] && (all->line[all->i] == ' '
	|| all->line[all->i] == '\t'))
		++all->i;
}

void    cheackmet(char *str)
{
	unsigned i;
	unsigned j;

	i = 0;
	while(str[i])
	{
		j = 0;
		while(LABEL_CHARS[j])
		{
			if (str[i] != LABEL_CHARS[j])
				++j;
			else
				break;
		}
		!LABEL_CHARS[j] ? ft_error(1) : 0;
		++i;
	}
}

void	checkform(t_all *all)
{
	while (get_next_line(all->fd, &all->line))
	{
		all->i = 0;
		while (all->line[all->i])
		{
			if (all->line[all->i] == COMMENT_CHAR || all->line[all->i] == ALT_COMMENT_CHAR)
			{
				free(all->line);
				all->line = NULL;
				break ;
			}
			if (all->line[all->i] == ' ' || all->line[all->i] == '\t')
				++all->i;
			else
				return ;
			++all->st;
		}
		free(all->line);
		all->line = NULL;
	}
}

int		last_check(t_all *all)
{
	char	c;
	char	ac;

	c = COMMENT_CHAR;
	ac = ALT_COMMENT_CHAR;
	while (all->line[all->i])
	{
		if (all->line[all->i] == ' ' || all->line[all->i] == '\t')
			++all->i;
		else if (all->line[all->i] == c || all->line[all->i] == ac)
			break ;
		else
			{
				free(all->line);
				all->line = NULL;
				return (1);
			}
		++all->st;
	}
	free(all->line);
	all->line = NULL;
	all->i = 0;
	++all->st;
	return (0);
}

void	checkname(t_all *all, int f)
{
	size_t		i;
	unsigned	length;

	i = 0;
	length = f == 0 ? PROG_NAME_LENGTH : COMMENT_LENGTH;
	quick_pass(all);
	all->line[all->i] && all->line[all->i]  == '"' ? ++all->i : ft_error(1);
	while(i < length && all->line[all->i] != '"')
	{
		while (!all->line[all->i])
		{
			f == 0 ? all->prog_name[i] = '\n' : 0;
			f == 1 ? all->comment[i] = '\n' : 0;
			++all->st;
			free(all->line);
			all->line = NULL;
			all->i = 0;
			++i;
			if (!get_next_line(all->fd, &all->line))
				break ;
		}
		if (all->line[all->i] == '"')
			break ;
		f == 0 ? all->prog_name[i] = all->line[all->i] : 0;
		f == 1 ? all->comment[i] = all->line[all->i] : 0;
		++i;
		++all->i;
	}
	i == length && all->line[all->i] != '"' ? ft_error(1) : ++all->i;
	last_check(all) ? ft_error(1) : 0;
}

int cheak_name_and_comment(t_all *all, int f)
{
	unsigned	i;
	unsigned	j;
	char		*str;

	i = 0;
	j = all->i;
	str = f == 0 ? NAME_CMD_STRING : COMMENT_CMD_STRING;
	while(str[i])
	{
		if (all->line[all->i] == str[i])
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

void	readfile(t_all *all)
{
	char		str[2];

	ft_bzero(&str, 2);
	all->magic = COREWAR_EXEC_MAGIC;
	while(!str[0] || !str[1])
	{
		checkform(all);
		!all->line ? ft_error(0) : 0;
		if (cheak_name_and_comment(all, 0))
		{
			str[0] = 1;
			checkname(all, 0);
		}
		else if (cheak_name_and_comment(all, 1))
		{
			str[1] = 1;
			checkname(all, 1);
		}
		else
			ft_error(1);
	}
	ft_printf("%s\n", all->prog_name);
	ft_printf("%s\n", all->comment);
}

void	checkmakros(void)
{
	NAME_CMD_STRING <= 0 || PROG_NAME_LENGTH <= 0 ||
	COMMENT_LENGTH <= 0 || !COREWAR_EXEC_MAGIC ||
	!COMMENT_CMD_STRING || !ALT_COMMENT_CHAR  || !LABEL_CHAR ||
	!DIRECT_CHAR || !SEPARATOR_CHAR || !LABEL_CHARS || REG_NUMBER <= 0 ||
	CYCLE_TO_DIE <= 0 || CYCLE_DELTA <= 0 || NBR_LIVE <= 0 || MAX_CHECKS <= 0
	|| IND_SIZE <= 0  || REG_SIZE <= 0 || !DIR_SIZE || REG_CODE <= 0 ||
	DIR_CODE <= 0 || IND_CODE <= 0 || MAX_ARGS_NUMBER <= 0 || MAX_PLAYERS <= 0
	|| MEM_SIZE <= 0 || T_REG <= 0 || T_DIR <= 0 || T_IND <= 0 || T_LAB <= 0?
	ft_error(1) : 0;
}

int main(int a, char **b)
{
	int fd;
	t_all	all;
	if (a != 2)
	{
		write(2, "usage", 5);
		exit(1);
	}
	checkmakros();
	fd = ft_read_file(b[1]);
	ft_bzero(&all, sizeof(all));
	all.fd = fd;
	readfile(&all);
	close(fd);
	return (0);
}