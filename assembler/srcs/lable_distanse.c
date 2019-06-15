/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lable_distanse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 02:58:54 by gabshire          #+#    #+#             */
/*   Updated: 2019/06/15 02:59:55 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	label_distanse_mp(t_tokens *token, t_tokens *copyscan,
		int *k, t_tokens *s)
{
	int f;

	f = 0;
	if (!ft_strcmp(copyscan->str, token->str) && (copyscan->tp == DIRLABEL
	|| copyscan->tp == INDIRLABEL) && copyscan->st == s->st)
	{
		k[0] = 0;
		f = 1;
	}
	return (f);
}

static int	label_distanse_m(t_tokens *token, t_list *parseng,
							t_all *all, t_tokens *s)
{
	t_tokens	*copyscan;
	int			r;
	int			f;
	int			k;

	f = 0;
	r = 0;
	while (parseng)
	{
		k = 0;
		copyscan = parseng->content;
		while (copyscan)
		{
			k += copyscan->size;
			if ((f = label_distanse_mp(token, copyscan, &k, s)))
				break ;
			copyscan = copyscan->next;
		}
		r += k;
		if (f)
			break ;
		parseng = parseng->next;
	}
	!parseng && unknown_label_error(all, s);
	return (-r);
}

static int	label_distanse_pr(t_tokens *copyscan, int *f, char *str)
{
	int r;

	r = 0;
	while (copyscan)
	{
		r += copyscan->size;
		if (!ft_strcmp(copyscan->str, str) && copyscan->tp == LABEL)
		{
			f[0] = 1;
			break ;
		}
		copyscan = copyscan->next;
	}
	return (r);
}

static int	label_distanse_p(t_list *parseng, t_all *all, t_tokens *token)
{
	t_tokens	*copyscan;
	int			r;
	int			f;
	char		*str;

	f = 0;
	r = 0;
	copyscan = parseng->content;
	str = token->str;
	while (copyscan)
	{
		r += copyscan->size;
		copyscan = copyscan->next;
	}
	parseng = parseng->next;
	while (parseng)
	{
		copyscan = parseng->content;
		r += label_distanse_pr(copyscan, &f, str);
		if (f)
			break ;
		parseng = parseng->next;
	}
	!parseng && unknown_label_error(all, token);
	return (r);
}

int			label_distance(t_tokens *token, t_all *all)
{
	t_tokens	*copyscan;
	int			r;
	t_list		*parseng;

	parseng = all->parsing;
	copyscan = parseng->content;
	while (parseng)
	{
		copyscan = parseng->content;
		if ((copyscan->st == token->st)
			|| (!ft_strcmp(copyscan->str, token->str) && (copyscan->tp == LABEL
			|| copyscan->tp == DIRLABEL || copyscan->tp == INDIRLABEL)))
			break ;
		parseng = parseng->next;
	}
	if (token->st > copyscan->st)
		r = label_distanse_m(copyscan, parseng, all, token);
	else
		r = label_distanse_p(parseng, all, token);
	return (r);
}
