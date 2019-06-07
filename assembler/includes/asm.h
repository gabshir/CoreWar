/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 21:47:20 by jwillem-          #+#    #+#             */
/*   Updated: 2019/06/05 18:19:55 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "op.h"


/*
 * str имя метки, при следующем заходе значение меняется на распознанное число
 */

typedef struct			s_tokens
{
	char 				*str;
	unsigned int		st;
	unsigned int		i;
	unsigned char		tp;
	struct 	s_tokens *next;
}						t_tokens;


/*
* fd - файловый дискриптор
* magic - магическое число
* parseng - результат работы парсера
* i - индекс в строке
* st - номер строки
*/

typedef struct			s_all
{
	int				fd;
	unsigned int	i;
	unsigned int	st;
	char			*line;
	unsigned int	magic;
	char			prog_name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
	unsigned int	prog_size;
	t_list			*parsing;
	t_tokens		*temp;
}						t_all;

/*
 * работа с листами токинов
 */

t_tokens	*ft_newtokens(t_all *all, unsigned char tp);
void		ft_tokenspush(t_tokens **alst, t_tokens *new);
void		ft_tokensadd(t_tokens **alst, t_tokens *new);

void		ft_error(t_all *all, int er);
int			last_check(t_all *all);
int			checkform(t_all *all);
void		parseng(t_all *all);
void		quick_pass(t_all *all);
t_op		operations(t_all *all);

#endif
