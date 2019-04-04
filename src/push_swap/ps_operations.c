/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_operations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 23:06:00 by akupriia          #+#    #+#             */
/*   Updated: 2019/04/04 23:13:48 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

int		*shift_back(int *arr, int *n)
{
	// int *tmp;
	int i;

	i = (*n)++;
	while (--i > -1)
		arr[i + 1] = arr[i];
	return (arr);
}

void	ra(t_stack *stack)
{
	int		elem;
	int		i;
	char	*s;

	if (stack->num_1 > 1)
	{
		i = -1;
		elem = stack->st1[0];
		while (++i < stack->num_1 - 1)
			stack->st1[i] = stack->st1[i + 1];
		stack->st1[i] = elem;
		s = ft_strdup("ra\n");
		ft_lstpush(&op_list, ft_lstnew(s, 3));
		free(s);
	}
}

void	rb(t_stack *stack)
{
	int		elem;
	int		i;
	char	*s;

	if (stack->num_2 > 1)
	{
		i = -1;
		elem = stack->st2[0];
		while (++i < stack->num_2 - 1)
			stack->st2[i] = stack->st2[i + 1];
		stack->st2[i] = elem;
		s = ft_strdup("rb\n");
		ft_lstpush(&op_list, ft_lstnew(s, 3));
		free(s);
	}
}

void	rra(t_stack *stack)
{
	int		elem;
	int		i;
	char	*s;

	if (stack->num_1 > 1)
	{
		i = stack->num_1;
		elem = stack->st1[stack->num_1 - 1];
		while (--i > 0)
			stack->st1[i] = stack->st1[i - 1];
		stack->st1[i] = elem;
		s = ft_strdup("rra\n");
		ft_lstpush(&op_list, ft_lstnew(s, 4));
		free(s);
	}
}

void	rrb(t_stack *stack)
{
	int		elem;
	int		i;
	char	*s;

	if (stack->num_2 > 1)
	{
		i = stack->num_2;
		elem = stack->st2[stack->num_2 - 1];
		while (--i > 0)
			stack->st2[i] = stack->st2[i - 1];
		stack->st2[i] = elem;
		s = ft_strdup("rrb\n");
		ft_lstpush(&op_list, ft_lstnew(s, 4));
		free(s);
	}
}
