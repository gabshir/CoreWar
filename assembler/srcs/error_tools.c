/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 05:14:53 by jwillem-          #+#    #+#             */
/*   Updated: 2019/06/13 05:25:26 by jwillem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				memory_error(void)
{
	ft_printf("ERROR: Couldn't allocate memory.\n");
	exit(1);
	return (1);
}

int				unknown_label_error(t_all *all, t_tokens *token)
{
	all->i = token->i - ft_strlen(token->str);
	all->st = token->st;
	ft_error(all, Semantic, Label_not_found);
	return (1);
}

static t_error	*create_error(t_all *all, t_er_type type, t_case_type reason)
{
	t_error	*error;

	SECURE_MALLOC(error = ft_memalloc(sizeof(t_error)));
	error->type = type;
	error->reason = reason;
	error->line = SPLIT;
	error->st = all->st;
	error->i = all->i;
	error->next = NULL;
	return (error);
}

static void		error_push(t_all *parser, t_error *error)
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

void			ft_error(t_all *all, t_er_type type, t_case_type reason)
{
	if (type == Lexical)
		error_push(all, create_error(all, Lexical, reason));
	else if (type == Syntactic)
		error_push(all, create_error(all, Syntactic, reason));
	else if (type == Semantic)
		error_push(all, create_error(all, Semantic, reason));
}
