# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkremen <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/24 18:15:35 by vkremen           #+#    #+#              #
#    Updated: 2019/01/12 18:57:17 by vkremen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

FLAGS = -Wall -Werror -Wextra

SRC = 	./sources/main.c\
		./sources/reading.c\
		./sources/add_list.c\
		./sources/checking.c\
		./sources/error_management.c\
		./sources/validations.c\
		./sources/helpful_function.c\
		./sources/breadth_first_search.c\
		./sources/some_bonuses.c\
		./sources/print_result.c

OB = $(SRC:%.c=%.o) 

all: $(NAME)

%.o:%.c
	@gcc -c $(FLAGS) $< -o $@

$(NAME): $(OB)
	@make -C libft
	@gcc $(OB) libft/libft.a -o $(NAME)

clean: 
	@make clean -C libft
	@rm -f $(OB)

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)

re: fclean all
