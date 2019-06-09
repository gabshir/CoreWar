/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:37:16 by gabshire          #+#    #+#             */
/*   Updated: 2019/06/09 21:56:45 by jwillem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	quick_pass(t_all *all)
{
	while(all->line[all->i] && (all->line[all->i] == ' '
	|| all->line[all->i] == '\t'))
		++all->i;
}

int		checkform(t_all *all)
{
	int t;

	while ((t = get_next_line(all->fd, &all->line)))
	{
		all->i = 0;
		++all->st;
		if (all->pred_line)
		{
			free(all->pred_line);
			all->pred_line = NULL;
		}
		all->pred_line = ft_strdup(all->line);
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
				return (t);
		}
		if (all->line)
		{
			free(all->line);
			all->line = NULL;
		}
	}
	//free(all->line);
	all->line = all->pred_line;
	return (t);
}

int		checkform(t_all *all)
{	
	while ((all->line = &all->split[all->st]))
	{
		++all->st;
		all->i = 0;
		if (all->line[all->i] == COMMENT_CHAR || all->line[all->i] == ALT_COMMENT_CHAR)
			continue ;
		if (all->line[all->i] == ' ' || all->line[all->i] == '\t')
			all->i++;
		else
			return (1);
	}
	return (0);
}

int		last_check(t_all *all, int f)
{
	char	c;
	char	ac;

	c = COMMENT_CHAR;
	ac = ALT_COMMENT_CHAR;
	f ? all->line = all->pred_line : 0;
	while (all->line[all->i])
	{
		if (all->line[all->i] == ' ' || all->line[all->i] == '\t')
			++all->i;
		else if (all->line[all->i] == c || all->line[all->i] == ac)
			break ;
		else
			return (1);
	}
	free(all->line);
	all->line = NULL;
	all->i = 0;
	return (0);
}

void	checkname(t_all *all, int f)
{
	size_t		i;
	unsigned	length;

	i = 0;
	length = f == 0 ? PROG_NAME_LENGTH : COMMENT_LENGTH;
	quick_pass(all);
	all->line[all->i] && all->line[all->i]  == '"' ? ++all->i : ft_error(all, Syntactic, Wrong_argument);
	while(i < length && all->line[all->i] != '"')
	{
		while (!all->line[all->i])
		{
			f == 0 ? all->prog_name[i] = '\n' : 0;
			f == 1 ? all->comment[i] = '\n' : 0;
			free(all->line);
			all->line = NULL;
			all->i = 0;
			++i;
			if (!get_next_line(all->fd, &all->line))
				break ;
			else
				++all->st;
		}
		if (all->line[all->i] == '"')
			break ;
		f == 0 ? all->prog_name[i] = all->line[all->i] : 0;
		f == 1 ? all->comment[i] = all->line[all->i] : 0;
		++i;
		++all->i;
	}
	i == length && all->line[all->i] != '"' ? ft_error(all, Semantic, CMD_size_exceeded) : ++all->i;
	last_check(all, 0) ? ft_error(all, Syntactic, Wrong_argument) : 0;
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
	char		flags[2];

	ft_bzero(&flags, 2);
	all->magic = COREWAR_EXEC_MAGIC;
	while(!flags[0] || !flags[1])
	{
		checkform(all);
		!all->line ? ft_error(all, Semantic, Bad_CMD_declaration) : 0;
		if (cheak_name_and_comment(all, 0) && !flags[0])
		{
			flags[0] = 1;
			checkname(all, 0);
		}
		else if (cheak_name_and_comment(all, 1) && !flags[1])
		{
			flags[1] = 1;
			checkname(all, 1);
		}
		else
		{
			ft_error(all, Semantic, Bad_CMD_declaration);
			break ;
		}
	}
	// ft_printf("%s\n", all->prog_name);
	// ft_printf("%s\n", all->comment);
}

// void	checkmakros(void)
// {
// 	NAME_CMD_STRING <= 0 || PROG_NAME_LENGTH <= 0 ||
// 	COMMENT_LENGTH <= 0 || !COREWAR_EXEC_MAGIC ||
// 	!COMMENT_CMD_STRING || !ALT_COMMENT_CHAR  || !LABEL_CHAR ||
// 	!DIRECT_CHAR || !SEPARATOR_CHAR || !LABEL_CHARS || REG_NUMBER <= 0 ||
// 	CYCLE_TO_DIE <= 0 || CYCLE_DELTA <= 0 || NBR_LIVE <= 0 || MAX_CHECKS <= 0
// 	|| IND_SIZE <= 0  || REG_SIZE <= 0 || !DIR_SIZE || REG_CODE <= 0 ||
// 	DIR_CODE <= 0 || IND_CODE <= 0 || MAX_ARGS_NUMBER <= 0 || MAX_PLAYERS <= 0
// 	|| MEM_SIZE <= 0 || T_REG <= 0 || T_DIR <= 0 || T_IND <= 0 || T_LAB <= 0?
// 	ft_error(NULL, 1) : 0;
// }

static void	copy_text(t_all *all)
{
	char	*buffer;
	char	*champ;

	SECURE_MALLOC(buffer = ft_strnew(MEM_SIZE));
	champ = NULL;
	while (read(all->fd, buffer, MEM_SIZE) > 0)
		champ = ft_strjoin_free(champ, buffer, 3);
	if (champ[ft_strlen(champ) - 1] != '\n')
		ft_error(all, Syntactic, No_last_line);
	all->split = ft_strsplit(champ, '\n');
}

int main(int a, char **b)
{
	// int fd;
	t_all	all;
	t_tokens *read;

	if (a != 2)
	{
		write(2, "usage", 5);
		exit(1);
	}
	// checkmakros();
	ft_bzero(&all, sizeof(all));
	all.fd = ft_read_file(b[1]);
	copy_text(&all);
	readfile(&all);
	parseng(&all);
	if (all.errors)
		print_errors(&all, b[1]);
	while(all.parsing)
	{
		read = all.parsing->content;
		while(read)
		{
			ft_printf("%s ", read->str);
			read = read->next;
		}
		ft_printf("\n");
		all.parsing = all.parsing->next;
	}
	// assembler(&all);
	// while(all.source)
	// {
	// 	ft_printf("%s\n", all.source->content);
	// 	all.source = all.source->next;
	// }
	close(all.fd);
	return (0);
}