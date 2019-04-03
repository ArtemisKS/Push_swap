/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_operations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 23:06:00 by akupriia          #+#    #+#             */
/*   Updated: 2019/04/03 23:30:13 by akupriia         ###   ########.fr       */
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
		ft_lstpush(&op_list, ft_lstnew(ft_strdup("ra\n"), 3));
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
		ft_lstpush(&op_list, ft_lstnew(ft_strdup("rb\n"), 3));
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
		ft_lstpush(&op_list, ft_lstnew(ft_strdup("rra\n"), 4));
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
		ft_lstpush(&op_list, ft_lstnew(ft_strdup("rrb\n"), 4));
	}
}
