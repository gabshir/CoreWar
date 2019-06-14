/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cor_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlabadie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 16:56:30 by dlabadie          #+#    #+#             */
/*   Updated: 2019/06/05 16:56:33 by dlabadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "vm.h"

static int		btoi(const t_byte *bytecode, size_t size)
{
	int		result;
	char	sign;
	int		i;

	result = 0;
	sign = (char)(bytecode[0] & 0x80);
	i = 0;
	while (size)
	{
		if (sign)
			result += ((bytecode[size - 1] ^ 0xFF) << (i++ * 8));
		else
			result += bytecode[size - 1] << (i++ * 8);
		size--;
	}
	if (sign)
		result = ~(result);
	return (result);
}

static int		get4byte(int fd)
{
	ssize_t	size;
	t_byte	buffer[4];

	size = read(fd, &buffer, 4);
	if (size < 4)
		print_error(FILE);
	return (btoi(buffer, 4));
}

static char		*get_str(int fd, size_t len)
{
	ssize_t	size;
	char	*buffer;

	if (!(buffer = ft_strnew(len)))
		print_error(MALLOC);
	size = read(fd, buffer, len);
	if (size == -1 || size < (ssize_t)len)
		print_error(FILE);
	return (buffer);
}

static t_byte	*get_code(int fd, size_t len)
{
	ssize_t	size;
	t_byte	*buffer;
	t_byte	byte;

	if (!(buffer = malloc(len)))
		print_error(MALLOC);
	size = read(fd, buffer, len);
	if (size == -1 || size < (ssize_t)len || read(fd, &byte, 1) != 0)
		print_error(FILE);
	return (buffer);
}

t_player		*parse_cor_file(char *file, int id)
{
	t_player	*player;
	int			fd;

	player = init_player(id);
	if ((fd = open(file, O_RDONLY)) < 0)
		print_error(FILE);
	if (get4byte(fd) != COREWAR_EXEC_MAGIC)
		print_error("wrong magic constant");
	player->name = get_str(fd, PROG_NAME_LENGTH);
	if (get4byte(fd) != 0)
		print_error("no null byte");
	player->code_size = get4byte(fd);
	if ((player->code_size < 0) || (player->code_size > CHAMP_MAX_SIZE))
		print_error("wrong exec code size");
	player->comment = get_str(fd, COMMENT_LENGTH);
	if (get4byte(fd) != 0)
		print_error("no null byte");
	player->code = get_code(fd, (size_t)player->code_size);
	return (player);
}
