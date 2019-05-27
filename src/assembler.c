/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabshire <gabshire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:37:16 by gabshire          #+#    #+#             */
/*   Updated: 2019/05/27 21:58:18 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "op.h"

void	checkname(int fd, header_t *chemp)
{
	char *line;
	int len;
	int i;

	line = NULL;
	i = 0;
	get_next_line(fd, &line);
	!line ? ft_eroror(0) : 0;
	len = ft_strlen(NAME_CMD_STRING);
	ft_strncmp(NAME_CMD_STRING, line, len) ? ft_eroror(1) : 0;
	while(line[len] && (line[len] == ' ' || line[len] == '\t'))
		++len;
	line[len] && line[len] == '"' ? ++len : ft_eroror(1);
	while(i < PROG_NAME_LENGTH && line[len] && line[len] != '"')
	{
		chemp->prog_name[i] = line[len];
		++i;
		++len;
	}
	i <= PROG_NAME_LENGTH && line[len] != '"' ? ft_eroror(1) : 0;
	line[len] == '"' && line[len + 1] ? ft_eroror(1) : 0;
	free(line);

}

void	readfile(int fd)
{
	char *line;
	header_t chemp;

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