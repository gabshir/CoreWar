/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 19:55:57 by gabshire          #+#    #+#             */
/*   Updated: 2019/06/07 22:06:08 by jwillem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"



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
