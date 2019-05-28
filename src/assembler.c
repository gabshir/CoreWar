/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:37:16 by gabshire          #+#    #+#             */
/*   Updated: 2019/05/28 18:34:24 by jwillem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "op.h"

int        last_check(size_t i, const char *line)
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

size_t quick_pass(char *line)
{
	size_t i;

	i = 0;
	while (line[i] == ' ' || line[i] =='\t')
		++i;
	return (++i);
}

char    *checkform(int fd)
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

int	ft_strncmpm(char *s1, char *s2)
{
	int len;

	len  = 0;
	while (s1[len] && (s1[len] == ' ' || s1[len] == '\t'))
		++len;
	while (s1[len] && *s2)
	{
		if (s1[len] != *s2)
			return (-1);
		++len;
		++s2;
	}
	return (len);
}

void	checkname(int fd, t_header *chemp)
{
	char	*line;
	int		i;
	int		j;

	line = NULL;
	i = 0;
	get_next_line(fd, &line);
	!line ? ft_error(0) : 0;
	j = ft_strncmpm(line, NAME_CMD_STRING);
	j == -1 ? ft_error(1) : 0;
	while (line[j] && line[j] == ' ' && line[j] == '\t')
		++j;
	line[j] ? ++j : ft_error(1);
	line[j] && line[j] == '"' ? ++j : ft_error(1);
	while(i < PROG_NAME_LENGTH && line[j] && line[j] != '"')
	{
		chemp->prog_name[i] = line[j];
		++i;
		++j;
	}
	i <= PROG_NAME_LENGTH && line[j] != '"' ? ft_error(1) : ++j;
	line[j] ? ft_error(1) : 0;
	free(line);
	line = NULL;
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