/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_sorted.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 23:08:29 by akupriia          #+#    #+#             */
/*   Updated: 2018/07/27 23:08:30 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int		int_value(char *line)
{
	int		i;
	char	*s;
	int		min;

	i = -1;
	min = 0;
	s = "2147483647\0";
	if (line[++i] == '-')
		min = 1;
	while (line[++i])
		;
	if (((i > 10) && (!min)) || ((i > 11) & (min)))
		return (0);
	else if (i == 10 || i == 11)
	{
		i = -1;
		while (++i < 11)
		{
			if (line[i + min] < s[i])
				return (1);
			if (line[i + min] > s[i])
				return (0);
		}
	}
	return (1);
}

int		is_sorted(t_stack *stack)
{
	int i;

	i = 0;
	while (i < stack->num_1 - 1)
	{
		if (stack->st1[i] > stack->st1[i + 1])
			return (0);
		i++;
	}
	stack->sort_elem = stack->num_1;
	return (1);
}

int		is_sorted1(t_stack *stack)
{
	int i;

	i = 0;
	while (i < stack->num_1 - 1)
	{
		if (stack->st1[i + 1] - stack->st1[i] != 1)
			return (0);
		i++;
	}
	stack->sort_elem = stack->num_1;
	return (1);
}

int		is_rev_sorted_b(t_stack *stack)
{
	int i;

	i = 0;
	while (i < stack->num_2 - 1)
	{
		if (stack->st2[i] < stack->st2[i + 1])
			return (0);
		i++;
	}
	return (1);
}

int		is_rev_sorted_b_num(t_stack *stack, int n)
{
	int i;

	i = 0;
	while (i < n - 1)
	{
		if (stack->st2[i + 1] - stack->st2[i] != 1)
			return (0);
		i++;
	}
	return (1);
}
