# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/28 19:24:02 by vbrazas           #+#    #+#              #
#    Updated: 2019/04/02 21:39:54 by vbrazas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME	:=	libftprintf.a
LIB		:=	libft/
LIB_N	:=	libft.a
SRC_D	:=	src/
SRC		:=	ft_printf.c \
			char_nil_sth.c \
			dig_min.c \
			dig_plus.c \
			dig_plusnil.c \
			dig_pluswidth.c \
			file1.c \
			handle_char.c \
			handle_dig.c \
			handle_dig1.c \
			handle_pointer.c \
			handle_string.c \
			parse_flags.c \
			parse_spec.c \
			parse_specif.c \
			print_char.c \
			print_uni.c \
			print_unsigned.c \
			stfunc.c \
			str_min.c \
			str_nil.c \
			str_nil_sth.c \
			struni1.c \
			uns_nil.c

SRCS	:=	$(addprefix $(SRC_D), $(SRC))
OBJ_D	:=	.obj/
OBJ		:=	$(addprefix $(OBJ_D), $(SRCS:%.c=%.o))
CC		:=	clang
CFLAGS	:=	-Wall -Wextra -Werror -g


all: $(NAME)

$(NAME): $(OBJ_D) $(OBJ)
	make -C $(LIB)
	mv $(LIB)$(LIB_N) $(NAME)
	ar -r $(NAME) $(OBJ)
	ranlib $(NAME)

$(OBJ_D):
	mkdir -p $(OBJ_D)$(SRC_D)
$(OBJ_D)%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C $(LIB)
	rm -f $(OBJ)
fclean: clean
	make fclean -C $(LIB)
	rm -f $(NAME)
re: fclean all
