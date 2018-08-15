/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 17:55:45 by akupriia          #+#    #+#             */
/*   Updated: 2018/07/17 17:52:28 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "ft_printf/hdr/libftprintf.h"

typedef struct	s_stack
{
	int			*st1;
	int			*st2;
	int			num_1;
	int			num_2;
	int			el_num;
	int			*num_elem;
	int			ind;
	int			sum_elem;
	int			sort_elem;
	int			fl;
	int			op_fl;
	int			cnt[100];
	int			index;
	int			in;
	int			man : 1;
	int			debug : 1;
	int			visual : 1;
	int			color : 1;
}				t_stack;

typedef struct	s_oper
{
	char		*oper;
	void		(*func)(t_stack *);
}				t_oper;

int				num_cor(char *line, t_stack *stack);
void			swap(int *a, int *b);
int				int_value(char *line);
int				alg_func(t_stack *stack, int *i, int ft);
int				divide_conquer(t_stack *stack, int ft, int *n);
void			sort_3_elem(t_stack *stack, int n);
void			sa(t_stack *stack);
void			sb(t_stack *stack);
int				*shift_back(int *arr, int *n);
void			ra(t_stack *stack);
void			rb(t_stack *stack);
void			rra(t_stack *stack);
void			rrb(t_stack *stack);
void			pa(t_stack *stack);
void			pb(t_stack *stack);
t_stack			*init_stack(int ac);
int				is_sorted(t_stack *stack);
void			ft_error(int code);
void			init_numelem(t_stack *stack, int n);
void			parse_data(int ac, char **av, t_stack *stack);
void			print_stacks(t_stack *stack, int fl);
void			pa1(t_stack *stack);
void			rrb1(t_stack *stack);
void			rra1(t_stack *stack);
void			rb1(t_stack *stack);
void			pb1(t_stack *stack);
int				*shift_fw(int *arr, int *n);
void			sa1(t_stack *stack);
void			sb1(t_stack *stack);
void			ra1(t_stack *stack);
void			check(char *s, t_stack *stack);
void			ps_sort(t_stack *stack);
int				ps_partition1(t_stack *stack, int n);
int				partition_cycle1(t_stack *stack, int pivot, int n);
int				smaller_equal_than_pivot(t_stack *stack, int pivot);
int				top_a(t_stack *stack);
int				top_b(t_stack *stack);
int				ps_partition_b(t_stack *stack, int n);
int				ps_partition(t_stack *stack, int n);
int				find_pivot(t_stack *stack, int n);
int				find_pivot_b(t_stack *stack, int n);
int				bigger_equal_than_pivot(t_stack *stack, int pivot);
int				is_rev_sorted_b1(t_stack *stack, int n);
int				is_rev_sorted_b_num(t_stack *stack, int n);
int				is_rev_sorted_b(t_stack *stack);
int				is_sorted1(t_stack *stack);
int				pa_b(t_stack *stack, int n);
int				case3el(t_stack *stack);
void			rev_sort_3_elem_b(t_stack *stack, int n);
int				ps_partition_b(t_stack *stack, int n);
int				do_partition_b(t_stack *stack, int pivot, int n);
t_stack			*init_stack1(int ac);
void			do_rb(t_stack *stack, int cnt);
int				do_rb1(t_stack *stack, int cnt, int pivot);
int				find_pivot_b_back(t_stack *stack, int n);
int				if_n_bol_stack(t_stack *stack, int n, int *k);
int				if_n_men_stack(t_stack *stack, int n);
int				pa_sort_while_part(int fl, int *num, t_stack *stack);
int				if_cnt_condition(t_stack *stack, int *pivot, int *num);
int				bigger_elem(t_stack *stack);
int				if_fl_belem(t_stack *stack, int fl);
int				basic_pas_ifs(t_stack *stack, int ind_v);
void			determ_op_fl(t_stack *stack, char *s);
t_stack			*check_if_str(char *s, t_stack *stack);
t_stack			*main_ifs(int ac, char **av, t_stack *stack);
void			free_stack(t_stack *stack);
void			rrr(t_stack *stack);
void			rr(t_stack *stack);
void			ss(t_stack *stack);

#endif
