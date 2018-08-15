/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_piv_back.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 20:58:44 by akupriia          #+#    #+#             */
/*   Updated: 2018/08/02 20:58:44 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int		find_pivot_b_back(t_stack *stack, int n)
{
	int k;
	int i;
	int ind;

	k = -1;
	if (n >= stack->num_elem[stack->ind])
		i = if_n_men_stack(stack, n);
	else
		i = if_n_bol_stack(stack, n, &k);
	if (k < stack->num_elem[stack->ind] - n && k > -1)
		ind = k;
	else
		ind = i;
	return (stack->st2[ind]);
}

int		basic_pas_ifs(t_stack *stack, int ind_v)
{
	if (stack->index < 1)
		stack->index = 1;
	if (!stack->cnt[stack->index - 1] && stack->index > 1)
		stack->index--;
	if (!stack->num_elem[stack->ind])
		stack->ind--;
	if (!stack->num_elem[stack->in])
		stack->in--;
	if (stack->num_elem[stack->ind] > ind_v)
	{
		stack->in = stack->ind;
		ind_v = stack->num_elem[stack->in];
	}
	return (ind_v);
}

int		if_stack_cnt_b_3(t_stack *stack, int *sum, int *sum1)
{
	int i;
	int pivot;

	pivot = find_pivot_b_back(stack, stack->cnt[stack->index - 1]);
	if (stack->cnt[stack->index - 1] < stack->num_elem[stack->ind])
	{
		i = -1;
		while (stack->cnt[stack->index - 1] + ++i < stack->num_elem[stack->ind])
		{
			if (top_b(stack) <= pivot)
			{
				rb(stack);
				(*sum)++;
			}
			else
			{
				pa(stack);
				(*sum1)++;
			}
		}
		stack->num_elem[stack->ind] -= *sum1;
		stack->cnt[stack->index - 1] += *sum;
		*sum = 0;
	}
	return (pivot);
}

int		if_cnt_condition(t_stack *stack, int *pivot, int *num)
{
	int fl;
	int sum;
	int sum1;

	fl = 0;
	sum = 0;
	sum1 = 0;
	if (bigger_elem(stack))
	{
		if (stack->cnt[stack->index - 1] > 3)
		{
			*pivot = if_stack_cnt_b_3(stack, &sum, &sum1);
			*num = do_rb1(stack, stack->cnt[stack->index - 1], *pivot);
			*num += sum1;
			sum1 = 0;
			fl = 1;
		}
		else
			do_rb(stack, stack->cnt[stack->index - 1]);
		if (stack->index > 1)
			stack->in--;
		stack->index--;
		stack->cnt[stack->index] = 0;
	}
	return (fl);
}

int		pa_sort_while_part(int fl, int *num, t_stack *stack)
{
	if (!(fl))
		*num = ps_partition_b(stack, stack->num_elem[stack->ind]);
	if (*num > stack->num_1 - stack->sort_elem)
		*num = stack->num_1 - stack->sort_elem;
	if (is_sorted(stack) && !stack->num_2)
		return (1);
	if (is_sorted(stack))
		return (0);
	while (!(alg_func(stack, num, 0)))
		;
	return (0);
}
