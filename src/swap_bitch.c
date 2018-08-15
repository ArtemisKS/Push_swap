/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_bitch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 23:10:15 by akupriia          #+#    #+#             */
/*   Updated: 2018/07/27 23:10:16 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	swap(int *a, int *b)
{
	int t;

	t = *a;
	*a = *b;
	*b = t;
}

int		ps_partition_b(t_stack *stack, int n)
{
	int pivot;
	int res;

	if (is_rev_sorted_b_num(stack, n) && n > 2)
	{
		res = pa_b(stack, n);
		return (res);
	}
	if (n < 4)
	{
		rev_sort_3_elem_b(stack, n);
		res = pa_b(stack, n);
		return (res);
	}
	if (stack->st2[1] - stack->st2[0] == 1
		|| stack->st2[1] - stack->st2[0] == 2)
		sb(stack);
	if (!stack->num_elem[stack->ind])
		stack->ind--;
	pivot = find_pivot_b(stack, n);
	res = do_partition_b(stack, pivot, n);
	return (res);
}

int		do_rb_cnt(t_stack *stack, int pivot, int cnt)
{
	int res;
	int i;

	i = 0;
	res = 0;
	while (i < cnt)
	{
		if (stack->st2[stack->num_2 - 1] > pivot)
		{
			rrb(stack);
			pa(stack);
			stack->num_elem[stack->ind]--;
			res++;
		}
		else
			rrb(stack);
		i++;
	}
	return (res);
}

int		do_rb1_1(t_stack *stack, int pivot, int cnt)
{
	int res;
	int i;

	i = 0;
	res = 0;
	while (i < stack->num_2 - cnt)
	{
		if (stack->st2[stack->num_2 - 1] > pivot)
		{
			rb(stack);
			pa(stack);
			stack->num_elem[stack->ind]--;
			res++;
		}
		else
			rb(stack);
		i++;
	}
	return (res);
}

int		do_rb1(t_stack *stack, int cnt, int pivot)
{
	int res;

	res = 0;
	if (!stack->num_elem[stack->ind])
		stack->ind--;
	if (stack->num_2 > 6)
	{
		if (cnt < stack->num_2 / 2)
			res = do_rb_cnt(stack, pivot, cnt);
		else
			res = do_rb1_1(stack, pivot, cnt);
	}
	if (stack->st2[1] - stack->st2[0] == 1
		|| stack->st2[1] - stack->st2[0] == 2)
		sb(stack);
	return (res);
}
