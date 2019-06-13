/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 04:18:52 by jwillem-          #+#    #+#             */
/*   Updated: 2019/06/13 05:10:05 by jwillem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	copy_text(t_all *all)
{
	char	*buffer;
	char	*champ;
	int		bytes_read;

	SECURE_MALLOC(buffer = ft_strnew(MEM_SIZE));
	champ = NULL;
	while ((bytes_read = read(all->fd, buffer, MEM_SIZE)) > 0)
	{
		buffer[bytes_read] = '\0';
		champ = ft_strjoin_free(champ, buffer, 1);
	}
	if (!(all->split = cw_strsplit(champ)))
	{
		ft_printf("File is empty\n");
		exit(1);
	}
	free(buffer);
	free(champ);
}

static char	*change_file_extension(char *name)
{
	char	*ext_ptr;

	ext_ptr = &name[ft_strlen(name) - 1];
	ext_ptr = ft_strcpy(ext_ptr, "cor");
	return (name);
}

static void	assembler(char *file_name)
{
	t_all	all;
	char	*tmp;

	ft_bzero(&all, sizeof(all));
	all.st = -1;
	all.fd = ft_read_file(file_name);
	copy_text(&all);
	readfile(&all, file_name);
	parseng(&all);
	if (all.errors)
		print_errors(&all, file_name);
	close(all.fd);
	tmp = ft_strdup(file_name);
	file_name = change_file_extension(file_name);
	if ((all.fd = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0644)) == -1)
	{
		ft_printf("Error: couldn't create file %s\n", file_name);
		free(tmp);
		global_free(&all);
		exit(1);
	}
	translate_into_byte_code(&all, tmp);
	free(tmp);
}

static int	check_file_format(char *av)
{
	size_t	n_len;

	n_len = ft_strlen(av);
	if (!ft_strcmp(&av[n_len - 2], ".s"))
		return (1);
	else
		return (0);
}

int			main(int ac, char **av)
{
	if (ac == 2 && check_file_format(av[1]))
		assembler(av[1]);
	else
	{
		ft_printf(ERROR_GREEN "USAGE:\n");
		ft_printf(ERROR_WHITE "This program compiles only .s file, ");
		ft_printf("and only one at a time.\n" ANSI_COLOR_RESET);
	}
	return (0);
}
