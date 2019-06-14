# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlabadie <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/07 10:29:47 by dlabadie          #+#    #+#              #
#    Updated: 2019/06/07 10:29:49 by dlabadie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ../corewar

CC = gcc
FLAGS = -Wall -Wextra -Werror

OBJS	:= main.o \
cursor.o free.o ft_refactor.o initialization.o player.o \
input.o parse_arguments.o parse_cor_file.o \
output.o show_fight_field.o \
apply_operation.o check.o helpers_for_run.o run.o \
op_add.o op_and.o op_ld.o op_lfork.o op_lld.o op_or.o op_sti.o op_xor.o \
op_aff.o op_fork.o op_ldi.o op_live.o op_lldi.o op_st.o op_sub.o op_zjmp.o \
init.o the.o \
gets.o parse_flags.o

FT		:= ../libft/
FT_LIB	:= $(addprefix $(FT), libftprintf.a)
FT_INC	:= -I $(FT)/includes/
FT_LNK	:= -L $(FT) -lftprintf

ODIR	:= ./obj/
IDIR	:= ./includes/

SDIR	:= ./
VDIR	:= ./visual_machine/
GDIR	:= ./general/
INDIR	:= ./input/
RUNDIR	:= ./run/
OPDIR	:= ./run/op/
OUTDIR	:= ./output/

$(ODIR)%.o:$(SDIR)%.c
	gcc $(FLAGS) $(FT_INC) -I $(IDIR) -o $@ -c $<

$(ODIR)%.o:$(VDIR)%.c
	gcc $(FLAGS) $(FT_INC) -I $(IDIR) -o $@ -c $<

$(ODIR)%.o:$(GDIR)%.c
	gcc $(FLAGS) $(FT_INC) -I $(IDIR) -o $@ -c $<


$(ODIR)%.o:$(INDIR)%.c
	gcc $(FLAGS) $(FT_INC) -I $(IDIR) -o $@ -c $<


$(ODIR)%.o:$(RUNDIR)%.c
	gcc $(FLAGS) $(FT_INC) -I $(IDIR) -o $@ -c $<


$(ODIR)%.o:$(OUTDIR)%.c
	gcc $(FLAGS) $(FT_INC) -I $(IDIR) -o $@ -c $<

$(ODIR)%.o:$(OPDIR)%.c
	gcc $(FLAGS) $(FT_INC) -I $(IDIR) -o $@ -c $<


OFILES	:= $(addprefix $(ODIR),$(OBJS))


all: $(NAME)

$(FT_LIB):
	make -C $(FT)

obj:
	mkdir obj

$(NAME): obj $(FT_LIB) $(OFILES)
	gcc -lncurses -o $(NAME) $(OFILES) -I./includes/ $(FT_INC) $(FT_LNK)


clean:
	rm -fr $(ODIR)*.o
	make -C $(FT) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(FT) fclean

re: fclean all

.PHONY : all clean fclean re

