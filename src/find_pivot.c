/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_pivot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 23:05:07 by akupriia          #+#    #+#             */
/*   Updated: 2018/07/27 23:05:08 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

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

void	pa(t_stack *stack)
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
		ft_printf("pa\n");
	}
}

void	pb(t_stack *stack)
{
	int num;
	int *arr;

	if (stack->num_1 > 0)
	{
		num = stack->st1[0];
		stack->st1 = shift_fw(stack->st1, &stack->num_1);
		arr = stack->st2;
		stack->st2 = shift_back(stack->st2, &stack->num_2);
		stack->st2[0] = num;
		free(arr);
		ft_printf("pb\n");
	}
}

int		find_pivot(t_stack *stack, int n)
{
	int i;
	int j;
	int cnt;
	int cnt1;

	i = -1;
	cnt = 0;
	cnt1 = 0;
	while (++i < n)
	{
		j = 0;
		while (j < n)
		{
			if (stack->st1[i] > stack->st1[j])
				cnt++;
			else if (stack->st1[i] < stack->st1[j])
				cnt1++;
			j++;
		}
		if (((cnt == cnt1) && (n % 2)) || ((cnt == cnt1 - 1) && (!(n % 2))))
			break ;
		cnt = 0;
		cnt1 = 0;
	}
	return (stack->st1[i]);
}

int		find_pivot_b(t_stack *stack, int n)
{
	int i;
	int j;
	int cnt;
	int cnt1;

	i = -1;
	cnt = 0;
	cnt1 = 0;
	while (++i < n)
	{
		j = 0;
		while (j < n)
		{
			if (stack->st2[i] > stack->st2[j])
				cnt++;
			else if (stack->st2[i] < stack->st2[j])
				cnt1++;
			j++;
		}
		if (((cnt == cnt1) && (n % 2)) || ((cnt == cnt1 - 1) && (!(n % 2))))
			break ;
		cnt = 0;
		cnt1 = 0;
	}
	return (stack->st2[i]);
}
