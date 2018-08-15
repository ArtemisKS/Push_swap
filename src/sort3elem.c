/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort3elem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 23:03:35 by akupriia          #+#    #+#             */
/*   Updated: 2018/07/27 23:03:36 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	rev_sort_3_elem_b(t_stack *stack, int n)
{
	int pivot;

	if (is_rev_sorted_b1(stack, n) || case3el(stack))
		return ;
	if ((stack->st2[2] < stack->st2[1]
		&& stack->st2[2] < stack->st2[0]) || (n == 2))
	{
		sb(stack);
		return ;
	}
	pivot = find_pivot_b(stack, n);
	if (top_b(stack) < pivot)
	{
		sb(stack);
		rev_sort_3_elem_b(stack, n);
	}
	else if (top_b(stack) >= pivot)
	{
		pa(stack);
		if (top_b(stack) < pivot)
			sb(stack);
		pb(stack);
		if (top_b(stack) == pivot)
			sb(stack);
	}
}

int		smaller_equal_than_pivot(t_stack *stack, int pivot)
{
	int i;

	i = 0;
	while (i < stack->num_1)
		if (stack->st1[i++] <= pivot)
			return (1);
	return (0);
}

int		bigger_equal_than_pivot(t_stack *stack, int pivot)
{
	int i;

	i = 0;
	while (i < stack->num_2)
		if (stack->st2[i++] > pivot)
			return (1);
	return (0);
}

int		ps_partition(t_stack *stack, int n)
{
	int		i;
	int		pivot;

	if (is_sorted(stack))
		return (1);
	pivot = find_pivot(stack, n);
	i = 0;
	while (stack->st1[i++] <= pivot)
		;
	while (stack->st1[stack->num_1 - 1] <= pivot)
		rra(stack);
	while (smaller_equal_than_pivot(stack, pivot))
	{
		if ((top_a(stack) <= pivot))
		{
			pb(stack);
			stack->num_elem[stack->ind]++;
		}
		else
			ra(stack);
	}
	stack->sum_elem += stack->num_elem[stack->ind];
	return (1);
}

int		pa_b(t_stack *stack, int n)
{
	int i;

	i = 0;
	if (!stack->num_elem[stack->ind])
		stack->ind--;
	while (i < n)
	{
		pa(stack);
		stack->num_elem[stack->ind]--;
		i++;
	}
	return (n);
}
