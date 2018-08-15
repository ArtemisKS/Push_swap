/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   partitionB.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 22:37:39 by akupriia          #+#    #+#             */
/*   Updated: 2018/07/27 22:37:40 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int		case3el(t_stack *stack)
{
	if (stack->num_2 == 3)
	{
		if (stack->st2[1] < stack->st2[0] && stack->st2[2] > stack->st2[0])
			rrb(stack);
		else if (stack->st2[2] > stack->st2[0] && stack->st2[2] > stack->st2[1])
		{
			sb(stack);
			rrb(stack);
		}
		else if (stack->st2[2] < stack->st2[0] && stack->st2[2] > stack->st2[1])
		{
			sb(stack);
			rb(stack);
		}
		else if (stack->st2[2] < stack->st2[1] && stack->st2[2] > stack->st2[0])
			rb(stack);
		else if (stack->st2[2] < stack->st2[1] && stack->st2[2] < stack->st2[0])
			sb(stack);
		return (1);
	}
	return (0);
}

void	conditions_b(t_stack *stack)
{
	if (stack->st1[0] - stack->st1[1] == 1)
		sa(stack);
	if (is_sorted1(stack))
		;
	if (stack->st2[1] - stack->st2[0] == 1
		|| stack->st2[1] - stack->st2[0] == 2)
		sb(stack);
}

void	do_rb(t_stack *stack, int cnt)
{
	int i;

	i = 0;
	if (stack->num_2 > 6)
	{
		if (cnt < stack->num_2 / 2)
			while (i < cnt)
			{
				rrb(stack);
				i++;
			}
		else
			while (i < stack->num_2 - cnt)
			{
				rb(stack);
				i++;
			}
	}
	if (stack->st2[1] - stack->st2[0] == 1
		|| stack->st2[1] - stack->st2[0] == 2)
		sb(stack);
}

void	part_b_cycle(t_stack *stack, int pivot, int *res, int *cnt)
{
	if (!stack->num_elem[stack->ind])
		stack->ind--;
	if ((top_b(stack) > pivot))
	{
		pa(stack);
		stack->num_elem[stack->ind]--;
		(*res)++;
	}
	else
	{
		rb(stack);
		(*cnt)++;
	}
}

int		do_partition_b(t_stack *stack, int pivot, int n)
{
	int i;
	int res;
	int cnt;

	i = 0;
	cnt = 0;
	res = 0;
	n = 0;
	while (stack->st2[stack->num_2 - 1] > pivot)
		rrb(stack);
	while (bigger_equal_than_pivot(stack, pivot))
	{
		conditions_b(stack);
		if (is_rev_sorted_b1(stack, stack->num_2))
			res += pa_b(stack, stack->num_2);
		else
			part_b_cycle(stack, pivot, &res, &cnt);
		i++;
	}
	if (cnt < stack->num_2 / 2)
		stack->cnt[stack->index] = cnt;
	stack->index++;
	return (res);
}
