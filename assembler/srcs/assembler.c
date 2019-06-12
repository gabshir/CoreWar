/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:37:16 by gabshire          #+#    #+#             */
/*   Updated: 2019/06/12 20:45:38 by jwillem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	quick_pass(t_all *all)
{
	while(SPLIT[all->i] && (SPLIT[all->i] == ' ' || SPLIT[all->i] == '\t'))
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
			if (SPLIT[all->i] == COMMENT_CHAR || SPLIT[all->i] == ALT_COMMENT_CHAR || SPLIT[all->i] == '\n')
				break ;
			if (SPLIT[all->i] == ' ' || SPLIT[all->i] == '\t')
				all->i++;
			else
				return (1);
		}
		// ++all->st;
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
		if (SPLIT[all->i] == ' ' || SPLIT[all->i] == '\t' || SPLIT[all->i] == '\n')
			++all->i;
		else if (SPLIT[all->i] == c || SPLIT[all->i] == ac)
			break ;
		else
			return (1);
	}
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
	if (SPLIT[all->i] && SPLIT[all->i]  != '"')
	{
		ft_error(all, Syntactic, Wrong_argument);
		return ;
	}
	++all->i;
	// all->line[all->i] && all->line[all->i]  == '"' ? ++all->i : ft_error(all, Syntactic, Wrong_argument);
	while(i < length && SPLIT && SPLIT[all->i] != '"')
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
	i == length && SPLIT[all->i] != '"' ? ft_error(all, Semantic, CMD_size_exceeded) : ++all->i;
	last_check(all) ? ft_error(all, Syntactic, Wrong_argument) : 0;
}

int check_name_and_comment(t_all *all, int f)
{
	unsigned	i;
	unsigned	j;
	char		*str;

	i = 0;
	j = all->i;
	str = f == 0 ? NAME_CMD_STRING : COMMENT_CMD_STRING;
	while(str[i])
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

void	readfile(t_all *all, char *file_name)
{
	char	flags[2];

	ft_bzero(&flags, 2);
	all->magic = COREWAR_EXEC_MAGIC;
	while(!flags[0] || !flags[1])
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
	// ft_printf("%s\n%s\n", all->prog_name, all->comment);
}

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
	all->split = cw_strsplit(champ);
	free(buffer);
	free(champ);
}

static char	*change_file_extension(char *name)
{
	char	*reserved_ptr;
	char	*new_name;
	size_t	new_len;

	reserved_ptr = name;
	new_len = ft_strlen(name) + 2;
	SECURE_MALLOC(new_name = ft_strnew(new_len));
	new_name = ft_strcpy(new_name, name);
	reserved_ptr = &name[new_len - 3];
	reserved_ptr = ft_strcpy(reserved_ptr, "cor");
	return (name);
}

static void	assembler(char *file_name)
{
	t_all	all;

	ft_bzero(&all, sizeof(all));
	all.st = -1;
	all.fd = ft_read_file(file_name);
	copy_text(&all);
	readfile(&all, file_name);
	parseng(&all);
	if (all.errors)
		print_errors(&all, file_name);
//	while(all.parsing)	//	start debug
//	{
//		read = all.parsing->content;
//		while(read)
//		{
//			ft_printf("%s ", read->str);
//			read = read->next;
//		}
//		ft_printf("\n");
//		all.parsing = all.parsing->next;
//	}	//	finish debug
	close(all.fd);
	file_name = change_file_extension(file_name);
	if ((all.fd = open(file_name, O_WRONLY|O_TRUNC|O_CREAT, 0644)) == -1)
		exit(1);	//	надо будет расширить
	translate_into_byte_code(&all);
}

static int  check_file_format(char *av)
{
	size_t	n_len;

	n_len = ft_strlen(av);
	
	if (!ft_strcmp(&av[n_len - 2], ".s"))
		return (1);
	else
		return (0);
}

int main (int ac, char **av)
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
