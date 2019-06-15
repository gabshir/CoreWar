/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 19:55:57 by gabshire          #+#    #+#             */
/*   Updated: 2019/06/15 02:59:55 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	*get_reason_str_extra(t_case_type reason)
{
	char	*reas;

	reas = NULL;
	if (reason == No_colon_before)
		reas = "No colon before the label";
	else if (reason == No_colon_after)
		reas = "No colon after the label";
	else if (reason == No_comma)
		reas = "No comma (',') found between arguments";
	else if (reason == Unknown_instr)
		reas = "Unknown instruction";
	else if (reason == No_last_line)
		reas = "No last LINE FEED found";
	else if (reason == Label_not_found)
		reas = "Label linked as an argument is not found";
	return (reas);
}

static char	*get_reason_str(t_case_type reason)
{
	char	*reas;

	reas = NULL;
	if (reason == CMD_size_exceeded)
		reas = "Command size exceeded";
	else if (reason == Wrong_argument)
		reas = "Wrong type of argument";
	else if (reason == Wrong_lchar)
		reas = "Wrong label char";
	else if (reason == Odd_argument)
		reas = "Odd argument";
	else if (reason == Bad_CMD_declaration)
		reas = "Bad command declaration";
	else if (reason == Incorrect_int)
		reas = "Incorrect integer";
	else
		reas = get_reason_str_extra(reason);
	return (reas);
}

static char	*put_caret(t_error *error)
{
	char	*caret;
	int		i;

	SECURE_MALLOC(caret = ft_memalloc(ft_strlen(error->line) + 1));
	i = -1;
	while (error->line[++i])
	{
		if (i == error->i)
		{
			caret[i] = '^';
			if (error->reason == Odd_argument)
				while (error->line[++i])
					caret[i] = '~';
		}
		else if (error->line[i] == '\t')
			caret[i] = '\t';
		else
			caret[i] = ' ';
	}
	return (caret);
}

static char	*get_type_str(t_er_type type)
{
	char	*str;

	str = NULL;
	if (type == Lexical)
		str = "Lexical error";
	else if (type == Syntactic)
		str = "Syntactic error";
	else if (type == Semantic)
		str = "Semantic error";
	return (str);
}

void		print_errors(t_all *all, char *filename)
{
	t_error	*ptr;
	char	*caret;
	int		er_q;

	ptr = all->errors;
	er_q = 0;
	while (ptr)
	{
		caret = put_caret(ptr);
		ft_printf(ERROR_WHITE "%s:%d:%d: " ERROR_RED "%s: " \
			ERROR_WHITE "%s\n", filename, ptr->st + 1, \
			ptr->i + 1, get_type_str(ptr->type), get_reason_str(ptr->reason));
		ft_printf(ANSI_COLOR_RESET "%s", ptr->line);
		ptr->reason == No_last_line && ft_printf("\n");
		ft_printf(ERROR_GREEN "%s\n" ANSI_COLOR_RESET, caret);
		free(caret);
		er_q++;
		ptr = ptr->next;
	}
	ft_printf("\n%d %s generated.\n", er_q, er_q > 1 ? "errors" : "error");
	global_free(all);
	exit(1);
}
