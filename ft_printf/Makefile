# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/28 19:24:02 by vbrazas           #+#    #+#              #
#    Updated: 2018/06/03 21:47:54 by akupriia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libftprintf.a
LIB		=	libft/
LIB_N	=	libft.a
SRC_D	=	src/
SRC		=	$(SRC_D)ft_printf.c \
			$(SRC_D)char_nil_sth.c \
			$(SRC_D)dig_min.c \
			$(SRC_D)dig_plus.c \
			$(SRC_D)dig_plusnil.c \
			$(SRC_D)dig_pluswidth.c \
			$(SRC_D)file1.c \
			$(SRC_D)handle_char.c \
			$(SRC_D)handle_dig.c \
			$(SRC_D)handle_dig1.c \
			$(SRC_D)handle_pointer.c \
			$(SRC_D)handle_string.c \
			$(SRC_D)parse_flags.c \
			$(SRC_D)parse_spec.c \
			$(SRC_D)parse_specif.c \
			$(SRC_D)print_char.c \
			$(SRC_D)print_uni.c \
			$(SRC_D)print_unsigned.c \
			$(SRC_D)stfunc.c \
			$(SRC_D)str_min.c \
			$(SRC_D)str_nil.c \
			$(SRC_D)str_nil_sth.c \
			$(SRC_D)struni1.c \
			$(SRC_D)uns_nil.c
OBJ_D	=	obj/
OBJ		=	$(addprefix $(OBJ_D), $(SRC:.c=.o))
CFLAGS	=	-Wall -Wextra -Werror


all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIB)
	mv $(LIB)$(LIB_N) $(NAME)
	ar -r $(NAME) $(OBJ)
	ranlib $(NAME)

$(OBJ): | $(OBJ_D)

$(OBJ_D):
	mkdir -p $(OBJ_D)$(SRC_D)

$(OBJ_D)%.o: %.c
	gcc $(CFLAGS) -o $@ -c $<

clean:
	make clean -C libft
	rm -f $(OBJ)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)
	rm -rf $(OBJ_D)

re: fclean all

.PHONY: all clean fclean re
