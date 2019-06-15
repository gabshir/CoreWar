/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlabadie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 11:47:02 by dlabadie          #+#    #+#             */
/*   Updated: 2019/06/05 11:47:06 by dlabadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "libft.h"
# include "ft_printf.h"

# include <stdbool.h>
# include <stdlib.h>
# include "op.h"

# include <fcntl.h>
# include <curses.h>

# define INDEX(X)		((X) - 1)

# define FT_ABS(X)		(((X) < 0) ? (-(X)) : (X))

# define ARENA			vm->arena

# define MALLOC			"malloc's fail"
# define ANY			"unknown error"
# define FILE			"wrong file"
# define DEBUG			"you are fool!"

# define FIRST			0
# define SECOND			1
# define THIRD			2

# define OP_CODE_LEN	1
# define ARGS_CODE_LEN	1
# define REG_LEN		1

static unsigned char	g_arg_code[3] = {
	T_REG,
	T_DIR,
	T_IND
};

typedef int				t_register;
typedef unsigned char	t_byte;

typedef struct			s_visu
{
	int					row;
	int					col;
}						t_visu;

typedef struct			s_player
{
	int					id;
	char				*name;
	char				*comment;
	int					code_size;
	t_byte				*code;
	size_t				current_lives_num;
	size_t				previous_lives_num;
	ssize_t				last_live;
	struct s_player		*next;
}						t_player;

typedef struct			s_cursor
{
	char				carry;
	t_byte				op_code;
	ssize_t				last_live;
	int					cycles_to_exec;
	t_byte				args_types[3];
	int					pc;
	unsigned int		step;
	t_register			reg[REG_NUMBER];
	t_player			*player;
	struct s_cursor		*next;
}						t_cursor;

typedef struct			s_vm
{
	t_byte				arena[MEM_SIZE];
	t_player			*players[MAX_PLAYERS];
	int					players_num;
	t_player			*last_alive;
	t_cursor			*cursors;
	size_t				cursors_num;
	size_t				lives_num;
	ssize_t				cycles;
	ssize_t				cycles_to_die;
	ssize_t				cycles_after_check;
	size_t				checks_num;
	ssize_t				dump_cycle;
	int					dump_print_mode;
	char				visu;
	char				live;
	char				aff;
}						t_vm;

typedef struct			s_parser
{
	int					index;
	char				**arg;
	t_player			*player;
}						t_parser;

typedef struct			s_op
{
	char				*name;
	t_byte				code;
	t_byte				args_num;
	char				args_types_code;
	t_byte				args_types[3];
	char				modify_carry;
	t_byte				t_dir_size;
	unsigned int		cycles;
	void				(*func)(t_vm *, t_cursor *);

}						t_op;

void					op_live(t_vm *vm, t_cursor *pc);

void					op_ld(t_vm *vm, t_cursor *pc);

void					op_st(t_vm *vm, t_cursor *pc);

void					op_add(t_vm *vm, t_cursor *pc);

void					op_sub(t_vm *vm, t_cursor *pc);

void					op_and(t_vm *vm, t_cursor *cursor);

void					op_or(t_vm *vm, t_cursor *cursor);

void					op_xor(t_vm *vm, t_cursor *cursor);

void					op_zjmp(t_vm *vm, t_cursor *cursor);

void					op_ldi(t_vm *vm, t_cursor *cursor);

void					op_sti(t_vm *vm, t_cursor *cursor);

void					op_fork(t_vm *vm, t_cursor *cursor);

void					op_lld(t_vm *vm, t_cursor *cursor);

void					op_lldi(t_vm *vm, t_cursor *cursor);

void					op_lfork(t_vm *vm, t_cursor *cursor);

void					op_aff(t_vm *vm, t_cursor *cursor);

static t_op				g_op[16] = {
	{
		.name = "live",
		.code = 0x01,
		.args_num = 1,
		.args_types_code = false,
		.args_types = {T_DIR, 0, 0},
		.modify_carry = false,
		.t_dir_size = 4,
		.cycles = 10,
		.func = &op_live
	},
	{
		.name = "ld",
		.code = 0x02,
		.args_num = 2,
		.args_types_code = true,
		.args_types = {T_DIR | T_IND, T_REG, 0},
		.modify_carry = true,
		.t_dir_size = 4,
		.cycles = 5,
		.func = &op_ld
	},
	{
		.name = "st",
		.code = 0x03,
		.args_num = 2,
		.args_types_code = true,
		.args_types = {T_REG, T_REG | T_IND, 0},
		.modify_carry = false,
		.t_dir_size = 4,
		.cycles = 5,
		.func = &op_st
	},
	{
		.name = "add",
		.code = 0x04,
		.args_num = 3,
		.args_types_code = true,
		.args_types = {T_REG, T_REG, T_REG},
		.modify_carry = true,
		.t_dir_size = 4,
		.cycles = 10,
		.func = &op_add
	},
	{
		.name = "sub",
		.code = 0x05,
		.args_num = 3,
		.args_types_code = true,
		.args_types = {T_REG, T_REG, T_REG},
		.modify_carry = true,
		.t_dir_size = 4,
		.cycles = 10,
		.func = &op_sub
	},
	{
		.name = "and",
		.code = 0x06,
		.args_num = 3,
		.args_types_code = true,
		.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.modify_carry = true,
		.t_dir_size = 4,
		.cycles = 6,
		.func = &op_and
	},
	{
		.name = "or",
		.code = 0x07,
		.args_num = 3,
		.args_types_code = true,
		.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.modify_carry = true,
		.t_dir_size = 4,
		.cycles = 6,
		.func = &op_or
	},
	{
		.name = "xor",
		.code = 0x08,
		.args_num = 3,
		.args_types_code = true,
		.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.modify_carry = true,
		.t_dir_size = 4,
		.cycles = 6,
		.func = &op_xor
	},
	{
		.name = "zjmp",
		.code = 0x09,
		.args_num = 1,
		.args_types_code = false,
		.args_types = {T_DIR, 0, 0},
		.modify_carry = false,
		.t_dir_size = 2,
		.cycles = 20,
		.func = &op_zjmp
	},
	{
		.name = "ldi",
		.code = 0x0A,
		.args_num = 3,
		.args_types_code = true,
		.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
		.modify_carry = false,
		.t_dir_size = 2,
		.cycles = 25,
		.func = &op_ldi
	},
	{
		.name = "sti",
		.code = 0x0B,
		.args_num = 3,
		.args_types_code = true,
		.args_types = {T_REG, T_REG | T_DIR | T_IND, T_REG | T_DIR},
		.modify_carry = false,
		.t_dir_size = 2,
		.cycles = 25,
		.func = &op_sti
	},
	{
		.name = "fork",
		.code = 0x0C,
		.args_num = 1,
		.args_types_code = false,
		.args_types = {T_DIR, 0, 0},
		.modify_carry = false,
		.t_dir_size = 2,
		.cycles = 800,
		.func = &op_fork
	},
	{
		.name = "lld",
		.code = 0x0D,
		.args_num = 2,
		.args_types_code = true,
		.args_types = {T_DIR | T_IND, T_REG, 0},
		.modify_carry = true,
		.t_dir_size = 4,
		.cycles = 10,
		.func = &op_lld
	},
	{
		.name = "lldi",
		.code = 0x0E,
		.args_num = 3,
		.args_types_code = true,
		.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
		.modify_carry = true,
		.t_dir_size = 2,
		.cycles = 50,
		.func = &op_lldi
	},
	{
		.name = "lfork",
		.code = 0x0F,
		.args_num = 1,
		.args_types_code = false,
		.args_types = {T_DIR, 0, 0},
		.modify_carry = false,
		.t_dir_size = 2,
		.cycles = 1000,
		.func = &op_lfork
	},
	{
		.name = "aff",
		.code = 0x10,
		.args_num = 1,
		.args_types_code = true,
		.args_types = {T_REG, 0, 0},
		.modify_carry = false,
		.t_dir_size = 4,
		.cycles = 2,
		.func = &op_aff
	}
};

typedef struct			s_gets
{
	t_register			(*get)(t_vm *, t_cursor *);

}						t_gets;

t_register				get_reg(t_vm *vm, t_cursor *cursor);
t_register				get_dir(t_vm *vm, t_cursor *cursor);
t_register				get_ind(t_vm *vm, t_cursor *cursor);

static t_gets			g_gets[3] = {
	{
		.get = &get_reg
	},
	{
		.get = &get_dir
	},
	{
		.get = &get_ind
	}
};

void					init_arena(t_vm *vm);
t_vm					*init_vm(void);
t_cursor				*init_cursor(t_player *player, int pc);

t_player				*init_player(int id);
void					reload_players_list(t_vm *vm, t_player *player);
void					add_player(t_player **list, t_player *new);
t_player				*get_player(t_player *list, int id);

void					set_cursors(t_vm *vm);
void					add_cursor(t_cursor **list, t_cursor *new);
void					move_cursor(t_cursor *cursor);
t_cursor				*duplicate_cursor(t_cursor *cursor, int addr);
t_cursor				*erase_cursor(t_cursor *previous, t_cursor **delete);
int						cat_atoi(const char *str);
void					free_vm(t_vm **vm);

t_vm					*input(int argc, char **argv);
void					parse_flags(t_parser *parser, t_vm *vm);
t_player				*parse_cor_file(char *file, int id);
void					parse_visu(t_parser *parser, t_vm *vm);
void					parse_aff(t_parser *parser, t_vm *vm);
void					parse_live(t_parser *parser, t_vm *vm);

void					run(t_vm *vm);
void					the_check(t_vm *vm);
void					parse_types_code(t_vm *vm, t_cursor *cursor, t_op *op);
char					can_i_apply(t_cursor *cursor, t_vm *vm, t_op *op);
unsigned int			step_size(t_byte arg_type, t_op *op);
int						get_address(int addr);
void					ito_arena(t_byte *arena, int addr, int value, int size);
int						btoi_in_arena(const t_byte *arena, int addr, int size);

void					show_fight_field(t_vm *vm);
void					print_usage(void);
void					print_error(char *error);
void					print_winner(t_vm *vm);
void					print_introducing(t_player **players, int players_num);
void					print_arena(t_byte *arena, int print_mode);

void					print_visu(t_vm *vm);
void					info_joueur(t_vm *vm);
void					init_colors(void);
t_visu					init_visu(t_vm *vm);

void					print_arena_visu(t_vm *vm);
void					display_winner(t_vm *vm);

#endif
