/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:37:16 by gabshire          #+#    #+#             */
/*   Updated: 2019/05/29 19:16:03 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "op.h"

size_t quick_pass(const char *line, size_t i)
{
	while (line[i] == ' ' || line[i] =='\t')
		++i;
	return (i);
}

char	*checkform(int fd)
{
	char	*line;
	size_t	i;

	line = NULL;
	while (get_next_line(fd, &line))
	{
		i = 0;
		while (line[i])
		{
			if (line[i] == COMMENT_CHAR || line[i] == ALT_COMMENT_CHAR)
			{
				free(line);
				line = NULL;
				break ;
			}
			if (line[i] == ' ' || line[i] == '\t')
				++i;
			else
				return (line);
		}
		free(line);
		line = NULL;
	}
	return (NULL);
}

int		command_comparison(size_t i,const char *line, int f)
{
	size_t j;
	char *str;

	j = 0;
	str = f == 0 ? NAME_CMD_STRING : COMMENT_CMD_STRING;
	while (str[j] && line[i])
	{
		if (str[j] == line[i])
		{
			++j;
			++i;
		}
		else
			ft_error(1);
	}
	!line[i] && str[j] ? ft_error(1) : 0;
	line[i] && str[j] ? ft_error(1) : 0;
	return (i);
}

int		last_check(size_t i, char *line)
{
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			++i;
		else if (line[i] == COMMENT_CHAR || line[i] == ALT_COMMENT_CHAR)
			break ;
		else
			{
				free(line);
				line = NULL;
				return (1);
			}
	}
	free(line);
	line = NULL;
	return (0);
}

void	checkname(int fd, t_header *chemp, size_t j, char *line, int f)
{
	size_t		i;
	unsigned	length;

	i = 0;
	length = f == 0 ? PROG_NAME_LENGTH : COMMENT_LENGTH;
	j = command_comparison(j, line, f);
	j = quick_pass(line, j);
	line[j] && line[j] == '"' ? ++j : ft_error(1);
	while(i < length && line[j] != '"')
	{
		while (!line[j])
		{
			f == 0 ? chemp->prog_name[i] = '\n' : 0;
			f == 1 ? chemp->comment[i] = '\n' : 0;
			free(line);
			line = NULL;
			j = 0;
			++i;
			if (!get_next_line(fd, &line))
				break ;
		}
		if (line[j] == '"')
			break ;
		f == 0 ? chemp->prog_name[i] = line[j] : 0;
		f == 1 ? chemp->comment[i] = line[j] : 0;
		++i;
		++j;
	}
	i == length && line[j] != '"' ? ft_error(1) : ++j;
	last_check(j, line) ? ft_error(1) : 0;
}

void	readfile(int fd)
{
	char		*line;
	t_header	chemp;
	size_t		j;
	char		str[2];

	ft_bzero(&chemp, sizeof(chemp));
	ft_bzero(&str, 2);
	chemp.magic = COREWAR_EXEC_MAGIC;
	line = NULL;
	while(!str[0] || !str[1])
	{
		line = checkform(fd);
		!line ? ft_error(0) : 0;
		j = quick_pass(line, 0);
		line[j] != '.' ? ft_error(1) : 0;
		if (line[j + 1] && line[j + 1] == NAME_CMD_STRING[1])
		{
			str[0] = 1;
			checkname(fd, &chemp, j, line, 0);
		}
		else if (line[j + 1] && line[j + 1] == COMMENT_CMD_STRING[1])
		{
			str[1] = 1;
			checkname(fd, &chemp, j, line, 1);
		}
		else
			ft_error(1);
	}
	ft_printf("%s\n", chemp.prog_name);
	ft_printf("%s\n", chemp.comment);
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

void	cheackmet(const char *str)
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

int main(int a, char **b)
{
	int fd;
	if (a != 2)
	{
		write(2, "usage", 5);
		exit(1);
	}
	checkmakros();
	fd = ft_read_file(b[1]);
	readfile(fd);

	close(fd);
	return (0);
}