/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 20:57:56 by akupriia          #+#    #+#             */
/*   Updated: 2018/09/23 20:50:02 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

void	pa_sort(t_stack *stack)
{
	int num;
	int pivot;
	int ind_v;
	int fl;

	if (!stack->num_elem[stack->ind])
		stack->ind--;
	stack->in = stack->ind;
	pivot = 0;
	fl = 0;
	num = 0;
	ind_v = stack->num_elem[stack->in];
	while (stack->num_2)
	{
		ind_v = basic_pas_ifs(stack, ind_v);
		if ((stack->ind == stack->in && stack->cnt[stack->index - 1] <=
		stack->num_elem[stack->ind]) || (stack->cnt[stack->index - 1] <=
		stack->num_elem[stack->ind] && !stack->num_elem[stack->ind + 1]))
			fl = if_cnt_condition(stack, &pivot, &num);
		if (pa_sort_while_part(fl, &num, stack))
			return ;
		fl = 0;
	}
}

int		alg_func(t_stack *stack, int *i, int ft)
{
	if (is_sorted(stack))
		return (1);
	if (*i < 4)
	{
		sort_3_elem(stack, *i);
		return (1);
	}
	else
	{
		if (!ft)
		{
			if (divide_conquer(stack, ft, i))
			{
				if (!is_sorted(stack))
					sort_3_elem(stack, *i);
				return (1);
			}
		}
		else
		{
			divide_conquer(stack, ft, i);
		}
		return (0);
	}
}

int		divide_conquer(t_stack *stack, int ft, int *n)
{
	if (ft)
		while ((*n > 3) && !(is_sorted(stack)))
		{
			ps_partition(stack, *n);
			*n -= stack->num_elem[stack->ind];
			stack->ind++;
			if (alg_func(stack, n, ft))
				return (1);
		}
	else
		while ((stack->num_1 - stack->sort_elem > 3) && !(is_sorted(stack)))
		{
			ps_partition1(stack, *n);
			if (!stack->num_elem[stack->ind])
				stack->ind--;
			*n -= stack->num_elem[stack->ind];
			if (stack->num_elem[stack->ind] > 3)
				stack->in++;
			alg_func(stack, n, ft);
		}
	return (1);
}

void	ps_sort(t_stack *stack)
{
	int n;

	if (is_sorted(stack))
		return ;
	if (stack->num_1 < 4)
	{
		sort_3_elem(stack, stack->num_1);
		if (is_sorted(stack))
			return ;
	}
	n = stack->num_1;
	divide_conquer(stack, 1, &n);
	pa_sort(stack);
}

void	init_numelem(t_stack *stack, int n)
{
	int i;

	i = 0;
	while (i < n)
		stack->num_elem[i++] = 0;
}
