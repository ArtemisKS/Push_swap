/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 22:21:50 by akupriia          #+#    #+#             */
/*   Updated: 2018/07/27 22:21:51 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int		if_fl_belem(t_stack *stack, int fl)
{
	int i;
	int j;

	if (fl)
	{
		j = stack->num_2 - 1;
		if (stack->num_elem[stack->ind - 1] > stack->num_elem[stack->ind])
			while (j > stack->num_2 - 1 - stack->cnt[stack->index - 1])
			{
				i = 0;
				while (i < stack->num_elem[stack->ind])
				{
					if (stack->st2[j] > stack->st2[i++])
						return (1);
				}
				j--;
			}
	}
	return (0);
}

int		if_n_men_stack(t_stack *stack, int n)
{
	int i;
	int j;
	int cnt;
	int cnt1;

	i = stack->num_2;
	cnt = 0;
	cnt1 = 0;
	while (--i > stack->num_2 - 1 - n)
	{
		j = stack->num_2;
		while (--j > stack->num_2 - 1 - n)
		{
			if (stack->st2[i] > stack->st2[j])
				cnt++;
			else if (stack->st2[i] < stack->st2[j])
				cnt1++;
		}
		if (((cnt == cnt1) && (n % 2)) || ((cnt == cnt1 - 1) && (!(n % 2))))
			break ;
		cnt = 0;
		cnt1 = 0;
	}
	return (i);
}

int		k_cycle(t_stack *stack, int n, int *k, int *cnt1)
{
	int j;
	int cnt;

	cnt = 0;
	j = stack->num_2;
	while (--j > stack->num_2 - 1 - n)
	{
		if (stack->st2[*k] > stack->st2[j])
			cnt++;
		else if (stack->st2[*k] < stack->st2[j])
			(*cnt1)++;
	}
	j = -1;
	while (++j < stack->num_elem[stack->ind] - n)
	{
		if (stack->st2[*k] > stack->st2[j])
			cnt++;
		else if (stack->st2[*k] < stack->st2[j])
			(*cnt1)++;
	}
	return (cnt);
}

int		i_cycle(t_stack *stack, int n, int *i, int *cnt1)
{
	int j;
	int cnt;

	cnt = 0;
	j = stack->num_2;
	(*i)--;
	while (--j > stack->num_2 - 1 - n)
	{
		if (stack->st2[*i] > stack->st2[j])
			cnt++;
		else if (stack->st2[*i] < stack->st2[j])
			(*cnt1)++;
	}
	j = -1;
	while (++j < stack->num_elem[stack->ind] - n)
	{
		if (stack->st2[*i] > stack->st2[j])
			cnt++;
		else if (stack->st2[*i] < stack->st2[j])
			(*cnt1)++;
	}
	return (cnt);
}

int		if_n_bol_stack(t_stack *stack, int n, int *k)
{
	int i;
	int j;
	int cnt;
	int cnt1;

	i = stack->num_2;
	cnt1 = 0;
	while (i > stack->num_2 - 1 - n)
	{
		j = stack->num_2;
		if (++(*k) < stack->num_elem[stack->ind] - n)
			cnt = k_cycle(stack, n, k, &cnt1);
		else
			cnt = i_cycle(stack, n, &i, &cnt1);
		if (((cnt == cnt1) && (stack->num_elem[stack->ind] % 2))
			|| ((cnt == cnt1 - 1) && (!(stack->num_elem[stack->ind] % 2))))
			break ;
		cnt1 = 0;
	}
	return (i);
}
