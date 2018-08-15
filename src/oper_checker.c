/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 22:10:22 by akupriia          #+#    #+#             */
/*   Updated: 2018/07/27 22:10:23 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	rb1(t_stack *stack)
{
	int elem;
	int i;

	if (stack->num_2 > 1)
	{
		i = 0;
		elem = stack->st2[0];
		while (i < stack->num_2 - 1)
		{
			stack->st2[i] = stack->st2[i + 1];
			i++;
		}
		stack->st2[i] = elem;
	}
}

void	rra1(t_stack *stack)
{
	int elem;
	int i;

	if (stack->num_1 > 1)
	{
		i = stack->num_1 - 1;
		elem = stack->st1[stack->num_1 - 1];
		while (i > 0)
		{
			stack->st1[i] = stack->st1[i - 1];
			i--;
		}
		stack->st1[i] = elem;
	}
}

void	rrb1(t_stack *stack)
{
	int elem;
	int i;

	if (stack->num_2 > 1)
	{
		i = stack->num_2 - 1;
		elem = stack->st2[stack->num_2 - 1];
		while (i > 0)
		{
			stack->st2[i] = stack->st2[i - 1];
			i--;
		}
		stack->st2[i] = elem;
	}
}

int		*shift_fw(int *arr, int *n)
{
	int i;

	i = 0;
	(*n)--;
	while (i < *n)
	{
		arr[i] = arr[i + 1];
		i++;
	}
	arr[i] = 0;
	return (arr);
}

void	pa1(t_stack *stack)
{
	int num;
	int *arr;

	if (stack->num_2 > 0)
	{
		num = stack->st2[0];
		stack->st2 = shift_fw(stack->st2, &stack->num_2);
		arr = stack->st1;
		stack->st1 = shift_back(stack->st1, &stack->num_1);
		stack->st1[0] = num;
		free(arr);
	}
}
