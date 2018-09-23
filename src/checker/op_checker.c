/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 22:19:28 by akupriia          #+#    #+#             */
/*   Updated: 2018/09/23 20:50:02 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

void	swap(int *a, int *b)
{
	int t;

	t = *a;
	*a = *b;
	*b = t;
}

void	sa1(t_stack *stack)
{
	if (stack->num_1 > 1)
		swap(&stack->st1[0], &stack->st1[1]);
}

void	sb1(t_stack *stack)
{
	if (stack->num_2 > 1)
		swap(&stack->st2[0], &stack->st2[1]);
}

void	free_stack(t_stack *stack)
{
	free(stack->st1);
	free(stack->st2);
	free(stack);
}
