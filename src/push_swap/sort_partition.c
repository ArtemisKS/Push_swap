/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_partition.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 22:23:41 by akupriia          #+#    #+#             */
/*   Updated: 2018/09/23 20:50:02 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

int		best_case_ever(t_stack *stack, int pivot, int n)
{
	int i;

	i = 0;
	while (i < n)
		if (stack->st1[i++] <= pivot)
			return (0);
	return (1);
}

int		ps_partition1(t_stack *stack, int n)
{
	int	i;
	int	pivot;
	int	cnt;

	if (is_sorted(stack))
		return (1);
	pivot = find_pivot(stack, n);
	if (stack->num_elem[stack->ind])
		stack->ind++;
	cnt = partition_cycle1(stack, pivot, n);
	i = -1;
	if (cnt < stack->num_1 / 2)
		while (++i < cnt)
			rra(stack);
	else
		while (++i < stack->num_1 - cnt)
			ra(stack);
	if (stack->st2[1] - stack->st2[0] == 1
		|| stack->st2[1] - stack->st2[0] == 2)
		sb(stack);
	return (cnt);
}

int		partition_cycle1(t_stack *stack, int pivot, int n)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (smaller_equal_than_pivot(stack, pivot))
	{
		if (stack->st2[1] - stack->st2[0] == 1
			|| stack->st2[1] - stack->st2[0] == 2)
			sb(stack);
		if (top_a(stack) <= pivot)
		{
			pb(stack);
			stack->num_elem[stack->ind]++;
		}
		else if (best_case_ever(stack, pivot, n - i))
			break ;
		else
		{
			ra(stack);
			cnt++;
		}
		i++;
	}
	return (cnt);
}

int		cases3elem(t_stack *stack)
{
	if (is_sorted(stack))
		return (1);
	if (stack->num_1 == 3)
	{
		if (stack->st1[1] > stack->st1[0] && stack->st1[2] < stack->st1[0])
			rra(stack);
		else if (stack->st1[2] < stack->st1[0] && stack->st1[2] < stack->st1[1])
		{
			sa(stack);
			rra(stack);
		}
		else if (stack->st1[2] > stack->st1[0] && stack->st1[2] < stack->st1[1])
		{
			sa(stack);
			ra(stack);
		}
		else if (stack->st1[2] > stack->st1[1] && stack->st1[2] < stack->st1[0])
			ra(stack);
		else if (stack->st1[2] > stack->st1[1] && stack->st1[2] > stack->st1[0])
			sa(stack);
		stack->sort_elem += 3;
		return (1);
	}
	return (0);
}

void	sort_3_elem(t_stack *stack, int n)
{
	int pivot;

	if ((stack->st1[2] > stack->st1[1]
		&& stack->st1[2] > stack->st1[0]) || (n == 2))
		sa(stack);
	if (cases3elem(stack))
		return ;
	pivot = find_pivot(stack, n);
	if (top_a(stack) > pivot)
	{
		sa(stack);
		sort_3_elem(stack, n);
	}
	else if (top_a(stack) <= pivot)
	{
		pb(stack);
		if (top_a(stack) > pivot)
			sa(stack);
		pa(stack);
		if (top_a(stack) == pivot)
			sa(stack);
		if (is_sorted(stack))
			return ;
	}
}
