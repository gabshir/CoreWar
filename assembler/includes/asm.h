/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 21:47:20 by jwillem-          #+#    #+#             */
/*   Updated: 2019/06/15 02:59:55 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "op.h"

# define SECURE_MALLOC(a)	!(a) && memory_error()

# define ERROR_RED			"\x1b[91;1m"
# define ERROR_GREEN		"\x1b[92;1m"
# define ERROR_WHITE		"\x1b[97;1m"

# define SPLIT	all->split[all->st]

typedef enum	e_er_type
{
	Lexical,
	Syntactic,
	Semantic
}				t_er_type;

typedef enum	e_case_type
{
	CMD_size_exceeded,
	Wrong_argument,
	Wrong_lchar,
	Odd_argument,
	Bad_CMD_declaration,
	Incorrect_int,
	No_colon_before,
	No_colon_after,
	No_comma,
	Unknown_instr,
	No_last_line,
	Label_not_found,
}				t_case_type;

typedef struct	s_error
{
	t_er_type		type;
	t_case_type		reason;
	char			*line;
	int				st;
	int				i;
	struct s_error	*next;
}				t_error;

typedef enum	e_type
{
	LABEL,
	INSTRUCTION,
	DIRECT,
	DIRLABEL,
	INDIRECT,
	INDIRLABEL,
	REGISTER
}				t_type;

typedef enum	e_operation
{
	live,
	ld,
	st,
	add,
	sub,
	and,
	or,
	xor,
	zjmp,
	ldi,
	sti,
	ffork,
	lld,
	lldi,
	lfork,
	aff
}				t_operation;

typedef struct	s_tokens
{
	char			*str;
	unsigned int	st;
	unsigned int	i;
	t_type			tp;
	t_operation		operation;
	char			size;
	struct s_tokens	*next;
}				t_tokens;

/*
** fd - файловый дискриптор
** magic - магическое число
** parseng - результат работы парсера
** i - индекс в строке
** st - номер строки
*/

typedef struct	s_all
{
	int				fd;
	char			**split;
	unsigned int	i;
	unsigned int	st;
	unsigned int	magic;
	char			prog_name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
	unsigned int	prog_size;
	t_list			*parsing;
	t_tokens		*temp;
	t_error			*errors;
	char			*source;
}				t_all;

void			readfile(t_all *all, char *file_name);

/*
**	Parser tools
*/

void			parseng(t_all *all);
void			checkmet(t_all *all, t_type tp, char size, int *incorrect_lbl);
void			quick_pass(t_all *all);
int				checkform(t_all *all);
int				last_check(t_all *all);
char			*tablica(int c);
int				miniatoi(t_all *all);
int				ft_reg(t_all *all, int *k, char size);
int				ft_dir(t_all *all, int *k, t_operation op);
int				ft_idir(t_all *all, int *k, char size);
int				scan_met(t_all *all);
int				check_label_colon(t_all *all, unsigned i);
void			sep_char(t_all *all, int k);
int				vn_met(t_all *all, t_type tp, int *k, char size);
void			unknown_instr_error(t_all *all, int *size);
void			get_argument(t_all *all, int *k, t_operation op, \
					unsigned char arg);
int				bad_lbl_char_manage(t_all *all, int f, \
					int *incorrect_lbl, int i);

/*
**	Errors
*/

void			print_errors(t_all *all, char *filename);
int				memory_error(void);
void			ft_error(t_all *all, t_er_type type, t_case_type reason);
int				unknown_label_error(t_all *all, t_tokens *token);

/*
** работа с листами токинов
*/

t_tokens		*ft_newtokens(t_all *all, t_type tp, int o, char size);
void			ft_tokenspush(t_tokens **alst, t_tokens *new);

t_op			operations(t_all *all, int *i);

char			**cw_strsplit(char *champ);
void			translate_into_byte_code(t_all *all, char *file_name);

int				label_distance(t_tokens *token, t_all *all);
void			translate_to_bytecode(t_all *all, size_t size, int l);
void			operation_to_bytecode(t_all *all);
void			global_free(t_all *all);

#endif
