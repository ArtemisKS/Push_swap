# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/23 21:00:30 by akupriia          #+#    #+#              #
#    Updated: 2018/09/23 21:34:23 by akupriia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re mclean mfclean mre

NAME	:=	checker
LIB		:=	../../ft_printf/
LIB_N	:=	$(LIB)libftprintf.a

INC_D	:=	../../includes/
SRC_D	:=	./
OBJ_D	:=	.obj/

CC		:=	clang
CFLAGS	:=	-Wall -Wextra -Werror
IFLAGS	:=	-I $(INC_D)
LFLAGS	:=	-L $(LIB) -lftprintf

SRC		:=	check_operations checker checker_init dop_op_checker op_checker oper_checker parse_data

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
