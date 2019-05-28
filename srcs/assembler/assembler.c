/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:37:16 by gabshire          #+#    #+#             */
/*   Updated: 2019/05/28 18:36:50 by jwillem-         ###   ########.fr       */
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

int		command_comparison(size_t i,const char *line)
{
	size_t j;

	j = 0;
	!NAME_CMD_STRING ? ft_error(1) : 0;
	while (NAME_CMD_STRING[j] && line[i])
	{
		if (NAME_CMD_STRING[j] == line[i])
		{
			++j;
			++i;
		}
		else
			ft_error(1);
	}
	!line[i] && NAME_CMD_STRING[j] ? ft_error(1) : 0;
	line[i] && NAME_CMD_STRING[j] ? ft_error(1) : 0;
	return (i);
}

int		last_check(size_t i, const char *line)
{
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			++i;
		else if (line[i] == COMMENT_CHAR || line[i] == ALT_COMMENT_CHAR)
			break ;
		else
			return (1);
	}
	return (0);
}

void	checkname(int fd, t_header *chemp)
{
	char		*line;
	size_t		i;
	size_t		j;

	i = 0;
	line = checkform(fd);
	!line ? ft_error(0) : 0;
	j = quick_pass(line, 0);
	j = command_comparison(j, line);
	j = quick_pass(line, j);
	line[j] && line[j] == '"' ? ++j : ft_error(1);
	while(i < PROG_NAME_LENGTH && line[j] != '"')
	{
		chemp->prog_name[i] = line[j];
		++i;
		++j;
		if (!line[j])
		{
			free(line);
			line = NULL;
			chemp->prog_name[i] = '\n';
			++i;
			get_next_line(fd, &line);
			line ? j = 0 : ft_error(1);
		}
	}
	i == PROG_NAME_LENGTH && line[j] != '"' ? ft_error(1) : ++j;
	last_check(j, line) ? ft_error(1) : 0;
}

void	readfile(int fd)
{
	char *line;
	t_header chemp;

	ft_bzero(&chemp, sizeof(chemp));
	chemp.magic = COREWAR_EXEC_MAGIC;
	line = NULL;
	checkname(fd, &chemp);
	ft_printf("%s\n", chemp.prog_name);
}

int main(int a, char **b)
{
	int fd;
	if (a != 2)
	{
		write(2, "usage", 5);
		exit(1);
	}
	fd = ft_read_file(b[1]);
	readfile(fd);
	return (0);
}