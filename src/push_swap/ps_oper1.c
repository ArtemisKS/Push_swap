/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_oper1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 23:06:56 by akupriia          #+#    #+#             */
/*   Updated: 2019/04/02 22:15:26 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

int		is_rev_sorted_b1(t_stack *stack, int n)
{
	int i;

	i = -1;
	while (++i < n - 1)
		if (stack->st2[i] - stack->st2[i + 1] != 1)
			return (0);
	return (1);
}

int		top_a(t_stack *stack)
{
	return (stack->st1[0]);
}

int		top_b(t_stack *stack)
{
	return (stack->st2[0]);
}

void	sa(t_stack *stack)
{
	if (stack->num_1 > 1)
	{
		swap(&stack->st1[0], &stack->st1[1]);
		ft_lstpush(&op_list, ft_lstnew("sa\n", 3));
	}
}

void	sb(t_stack *stack)
{
	if (stack->num_2 > 1)
	{
		swap(&stack->st2[0], &stack->st2[1]);
		ft_lstpush(&op_list, ft_lstnew("sb\n", 3));
	}
}

void	rrr(t_stack *stack)
{
	rra(stack);
	rrb(stack);
}

void	ss(t_stack *stack)
{
	sa(stack);
	sb(stack);
}

void	rr(t_stack *stack)
{
	ra(stack);
	rb(stack);
}
