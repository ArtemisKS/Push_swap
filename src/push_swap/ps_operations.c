/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_operations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 23:06:00 by akupriia          #+#    #+#             */
/*   Updated: 2018/09/23 20:50:02 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

int		*shift_back(int *arr, int *n)
{
	int *tmp;
	int i;

	i = 1;
	(*n)++;
	tmp = (int*)malloc(sizeof(int) * (*n));
	tmp[0] = 0;
	while (i < *n)
	{
		tmp[i] = arr[i - 1];
		i++;
	}
	return (tmp);
}

void	ra(t_stack *stack)
{
	int elem;
	int i;

	if (stack->num_1 > 1)
	{
		i = 0;
		elem = stack->st1[0];
		while (i < stack->num_1 - 1)
		{
			stack->st1[i] = stack->st1[i + 1];
			i++;
		}
		stack->st1[i] = elem;
		ft_printf("ra\n");
	}
}

void	rb(t_stack *stack)
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
		ft_printf("rb\n");
	}
}

void	rra(t_stack *stack)
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
		ft_printf("rra\n");
	}
}

void	rrb(t_stack *stack)
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
		ft_printf("rrb\n");
	}
}
