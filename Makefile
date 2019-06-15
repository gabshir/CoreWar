# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlabadie <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/05 11:58:32 by dlabadie          #+#    #+#              #
#    Updated: 2019/06/05 16:43:13 by dlabadie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	make -C libft
	make -C assembler
	make -C virtual_machine

clean:
	make -C libft clean
	make -C assembler clean
	make -C virtual_machine clean

fclean:
	make -C libft fclean
	make -C assembler fclean
	make -C virtual_machine fclean

re: fclean
	make all

