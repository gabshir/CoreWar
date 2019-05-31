/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 21:47:20 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/31 14:46:33 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "op.h"

/*
* LABEL - метка
* OPERATION - операция
* DIRECT - прямой аргумент
* DIRECT_LABEL прямой аргумент - метка
* INDIRECT - относительный аргамент
* INDIRECT_LABEL - относительная метка
* REGISTER - регистор
* SEPARATOR - разделитель
*/

typedef enum
{
    LABEL,
    OPERATION,
    DIRECT,
    DIRECT_LABEL,
    INDIRECT,
    INDIRECT_LABEL,
    REGISTER,
    SEPARATOR
}   t_type;

/*
* content название токена
* st - строка на которой находится токен
* i - индекс внутри строки
* t - тип токена
* next - следующий токен в строке
*/

typedef struct		s_tokens
{
	char			*content;
	unsigned int	t;
	unsigned int	st;
	unsigned int	i;
	struct s_tokens	*next;
}					t_tokens;

/*
* st - строка на которой находится токен
* i - индекс внутри строки
* tokens - токены которые находятся внутри строки
* next - следующая строка с токенами
*/

typedef struct			s_parseng
{
	unsigned int	st;
	unsigned int	i;
	t_tokens		*tokens;
	struct s_parseng	*next;
}						t_parseng;

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
	unsigned int	prog_size;
	char			comment[COMMENT_LENGTH + 1];
	t_parseng		*parseng;
}						t_all;

#endif
