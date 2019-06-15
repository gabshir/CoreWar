# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/28 19:06:18 by jwillem-          #+#    #+#              #
#    Updated: 2019/06/15 02:59:55 by gabshire         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ../asm

CC = gcc
FLAGS = -Wall -Wextra -Werror -g

SRCDIR = srcs/
OBJDIR = obj/

FILES = main	assembler	error	op	parseng		tokens	cw_strsplit		\
	calc	lable_distanse	operation_to_bytecode	parser_tools	\
	parser_tools2	global_free		error_tools		argument_check
OBJ = $(addprefix $(OBJDIR),$(addsuffix .o,$(FILES)))

LIBFT = ../libft/libftprintf.a
INCDIR = -I ./includes
LIBLINK = -L ../libft -lftprintf
LIBINC = -I ../libft/includes

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C ../libft

$(OBJDIR):
	@echo "Creating object files directories..."
	@mkdir $(OBJDIR)
	@echo "Directories are created!"
	
$(OBJDIR)%.o: $(SRCDIR)%.c | $(OBJDIR)
	@$(CC) $(FLAGS) $(INCDIR) $(LIBINC) -c $< -o $@

$(NAME): $(OBJ)
	@echo "Compiling Assembler..."
	@$(CC) $(LIBLINK) -o $(NAME) $(OBJ) 
	@echo "Assembler is compiled!"

libclean:
	@make clean -C ../libft

clean: libclean
	@echo "Deleting Assembler object files..."
	@rm -rf $(OBJDIR)
	@echo "Assembler object files are deleted!"

fclean: clean
	@echo "Deleting executables..."
	@rm -rf $(NAME)
	@echo "Executables are deleted!"
	@make fclean -C ../libft
	@echo "Everything is cleaned!"

re: fclean
	@$(MAKE) all
