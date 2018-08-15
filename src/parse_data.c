/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 22:18:18 by akupriia          #+#    #+#             */
/*   Updated: 2018/07/27 22:18:18 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

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

void	ra1(t_stack *stack)
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
	}
}

void	init_numelem(t_stack *stack, int n)
{
	int i;

	i = 0;
	while (i < n)
		stack->num_elem[i++] = 0;
}

t_stack	*check_if_str(char *s, t_stack *stack)
{
	char	**arr;
	int		i;
	int		res;

	i = -1;
	arr = ft_strsplit(s, ' ');
	while (arr[++i])
		;
	free_stack(stack);
	stack = init_stack1(i + 1);
	i = -1;
	while (arr[++i])
	{
		if ((res = num_cor(arr[i], stack)) == 1)
			stack->st1[i] = ft_atoi(arr[i]);
		else if (res == -1)
			ft_error(1);
		else
			ft_error(3);
		stack->num_1++;
	}
	while (--i >= 0)
		free(arr[i]);
	free(arr);
	return (stack);
}

void	parse_data(int ac, char **av, t_stack *stack)
{
	int i;
	int ind;
	int res;

	i = 0;
	if ((stack->debug && !stack->color) || (stack->visual) || (stack->man))
		ind = 2;
	else if (stack->debug && stack->color)
		ind = 3;
	else
		ind = 1;
	while (ind < ac)
	{
		if ((res = num_cor(av[ind], stack)) == 1)
			stack->st1[i] = ft_atoi(av[ind]);
		else if (res == -1)
			ft_error(1);
		else
			ft_error(3);
		stack->num_1++;
		ind++;
		i++;
	}
	stack->el_num = stack->num_1;
}
