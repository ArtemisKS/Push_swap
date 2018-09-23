# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/23 20:51:01 by akupriia          #+#    #+#              #
#    Updated: 2018/09/23 21:34:31 by akupriia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re mclean mfclean mre

NAME	:=	push_swap
LIB		:=	../../ft_printf/
LIB_N	:=	$(LIB)libftprintf.a

INC_D	:=	../../includes/
SRC_D	:=	./
OBJ_D	:=	.obj/

CC		:=	clang
CFLAGS	:=	-Wall -Wextra -Werror
IFLAGS	:=	-I $(INC_D)
LFLAGS	:=	-L $(LIB) -lftprintf

SRC		:=	big_elem check_if_sorted find_piv_back find_pivot pa_sort partition_b \
			ps_oper1 ps_operations ps_sort push_swap sort3elem sort_partition swap_bitch

SRCS	:=	$(addprefix $(SRC_D), $(addsuffix .c, $(SRC)))
OBJS	:=	$(addprefix $(OBJ_D), $(SRCS:%.c=%.o))
HDRS	:=	$(wildcard $(INC_D)*.h)

all: $(NAME)

$(NAME): $(LIB_N) $(OBJ_D) $(OBJS)
	$(CC) $(CFLAGS) $(IFLAGS) $(LFLAGS) $(OBJS) -o $(NAME)
$(LIB_N):
	make -C $(LIB)

$(OBJ_D):
	mkdir -p $(OBJ_D)$(SRC_D)
$(OBJ_D)%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

mclean:
	rm -rf $(OBJ_D)
mfclean: mclean
	rm -f $(NAME)
mre: mfclean all

clean:
	make clean -C $(LIB)
	rm -rf $(OBJ_D)
fclean: clean
	make fclean -C $(LIB)
	rm -f $(NAME)
re: fclean all
