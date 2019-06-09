/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 19:55:57 by gabshire          #+#    #+#             */
/*   Updated: 2019/06/09 22:08:44 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		memory_error(void)
{
	ft_printf("ERROR: Couldn't allocate memory.\n");
	exit(1);
	return (1);
}

static t_error	*create_error(t_all *parser, t_er_type type, t_case_type reason)
{
	t_error	*error;

	SECURE_MALLOC(error = ft_memalloc(sizeof(t_error)));
	error->type = type;
	error->reason = reason;
	error->line = ft_strdup(parser->line);
	error->st = parser->st;
	error->i = parser->i;
	error->next = NULL;
	return (error);
}

static void	error_push(t_all *parser, t_error *error)
{
	t_error	*ptr;

	if (parser->errors)
	{
		ptr = parser->errors;
		while (ptr)
			if (ptr->next)
				ptr = ptr->next;
			else
			{
				ptr->next = error;
				break ;
			}
	}
	else
		parser->errors = error;	
}

// void	lexical_error(t_all *parser, char *line)
// {
// 	error_push(parser, create_error(parser, Lexical));
// 	// ft_printf("line: %d, column: %d --> %s", parser->ln, parser->col, line);
// 	// ft_printf("Lexical error");
// }

// void	semantic_error(t_all *parser, char *line)
// {
// 	error_push(parser, create_error(parser, Semantic));
// }

void	ft_error(t_all *all, t_er_type type, t_case_type reason/*, int er */)
{
	if (type == Lexical)
		error_push(all, create_error(all, Lexical, reason));
	else if (type == Syntactic)
		error_push(all, create_error(all, Syntactic, reason));
	else if (type == Semantic)
		error_push(all, create_error(all, Semantic, reason));
	
	// !all ?  ft_printf("error makros \n") : 0;
	// er == 0 ? ft_printf("clean file\n") : 0;
	// er == 1 ? ft_printf("stroka %d stolbec %d syntax error\n", all->st, all->i) : 0;
	// ft_printf("%s\n", all->line);
	// exit(1);
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
	else if (reason == No_colon_before)
		reas = "No colon before the label";
	else if (reason == No_colon_after)
		reas = "No colon after the label";
	else if (reason == No_comma)
		reas = "No comma (',') found between arguments";
	else if (reason == Uknown_instr)
		reas = "Uknown instruction";
	else if (reason == No_last_line)
		reas = "No last empty line found";
	return (reas);
}

static char	*put_caret(t_error *error)
{
	char	*caret;
	int		i;

	SECURE_MALLOC(caret = ft_memalloc(ft_strlen(error->line) + 1));
	i = -1;
	if (!error->line)
		exit(1);
	while (error->line[++i])
	{
		if (error->line[i] == '\t')
			caret[i] = '\t';
		else if (i == error->i)
			caret[i] = '^';
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

void	print_errors(t_all *all, char *filename)
{
	t_error	*ptr;
	// char	*type;
	char	*caret;
	int		error_q;

	ptr = all->errors;
	error_q = 0;
	while (ptr)
	{
		// if (ptr->type == Lexical)
		// 	type = "Lexical error";
		// else if (ptr->type == Syntactic)
		// 	type = "Syntactic error";
		// else if (ptr->type == Semantic)
		// 	type = "Semantic error";
		caret = put_caret(ptr);
		ft_printf("%s:%d:%d: %s: %s\n", filename, ptr->st, ptr->i, get_type_str(ptr->type), get_reason_str(ptr->reason));
		ft_printf("%s\n%s\n", ptr->line, caret);
		free(caret);
		error_q++;
		ptr = ptr->next;
	}
	ft_printf("%d %s generated.\n", error_q, error_q > 1 ? "errors" : "error");
	exit(1);
}
