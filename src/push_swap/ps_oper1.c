/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_oper1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 23:06:56 by akupriia          #+#    #+#             */
/*   Updated: 2018/09/23 20:50:02 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

int		is_rev_sorted_b1(t_stack *stack, int n)
{
	int i;

	i = 0;
	while (i < n - 1)
	{
		if (stack->st2[i] - stack->st2[i + 1] != 1)
			return (0);
		i++;
	}
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
		ft_printf("sa\n");
	}
}

void	sb(t_stack *stack)
{
	if (stack->num_2 > 1)
	{
		swap(&stack->st2[0], &stack->st2[1]);
		ft_printf("sb\n");
	}
}
