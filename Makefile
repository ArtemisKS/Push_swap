#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akupriia <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/03 20:22:26 by akupriia          #+#    #+#              #
#    Updated: 2018/06/03 20:22:29 by akupriia         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	=	push_swap
CH_NAME =   checker
LIB		=	ft_printf/
LIB_HDR	=	$(LIB)hdr/
SRCD	=	src/
SRC		=	$(SRCD)push_swap.c \
            $(SRCD)check_if_sorted.c \
            $(SRCD)find_pivot.c \
            $(SRCD)pa_sort.c \
            $(SRCD)partition_b.c \
            $(SRCD)ps_oper1.c \
            $(SRCD)ps_operations.c \
            $(SRCD)sort3elem.c \
            $(SRCD)sort_partition.c \
            $(SRCD)swap_bitch.c \
            $(SRCD)ps_sort.c \
            $(SRCD)find_piv_back.c \
            $(SRCD)big_elem.c
CH_SRC  =   $(SRCD)checker.c \
            $(SRCD)oper_checker.c \
            $(SRCD)op_checker.c \
            $(SRCD)check_operations.c \
            $(SRCD)parse_data.c \
            $(SRCD)checker_init.c \
            $(SRCD)dop_op_checker.c
OBJ_D	=	obj/
OBJ_CH  =   obj_ch/
OBJ		=	$(addprefix $(OBJ_D), $(SRC:.c=.o))
CH_OBJ  =   $(addprefix $(OBJ_CH), $(CH_SRC:.c=.o))
LFLAGS	=	-lftprintf -L $(LIB)
IFLAGS	=	-I $(LIB_HDR) -I ./
CFLAGS	=	-Wall -Wextra -Werror


all: $(NAME) $(CH_NAME)

$(NAME): liball $(OBJ)
	gcc -o $(NAME) $(CFLAGS) $(OBJ) ft_printf/libftprintf.a

$(CH_NAME): liball $(CH_OBJ)
	gcc -o $(CH_NAME) $(CFLAGS) $(CH_OBJ) ft_printf/libftprintf.a

$(OBJ): | $(OBJ_D)

$(CH_OBJ): | $(OBJ_CH)

$(OBJ_D):
	mkdir -p $(OBJ_D)$(SRCD)

$(OBJ_D)%.o: %.c
	gcc $(CFLAGS) -o $@ -c $<

$(OBJ_CH):
	mkdir -p $(OBJ_CH)$(SRCD)

$(OBJ_CH)%.o: %.c
	gcc $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJ_D)
	rm -rf $(OBJ_CH)
	make clean -C $(LIB)

fclean: clean
	rm -f $(NAME)
	rm -f $(CH_NAME)
	make fclean -C $(LIB)

liball:
	make -C $(LIB)

re: fclean all

analyze: $(OBJ)
gcc -Wall -Wextra -pedantic -Werror -Winit-self -Wunreachable-code -Wformat-y2k -Wformat-nonliteral -Wformat-security -Wformat=2 -Wmissing-include-dirs -Wswitch-default -Wtrigraphs -Wstrict-overflow=5 -Wfloat-equal -Wundef -Wshadow -Wbad-function-cast -o $(NAME) $(LFLAGS) $(OBJ)

.PHONY: all clean fclean re