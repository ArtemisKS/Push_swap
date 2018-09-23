/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 22:14:44 by akupriia          #+#    #+#             */
/*   Updated: 2018/09/23 20:50:02 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

void	pb1(t_stack *stack)
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
	}
}

int		print_arr2(int arr[], int i, int fl, int num)
{
	if (((fl == 1 && num == 1) || (fl == 2 && num == 2)) && (i == 0))
	{
		ft_printf("{GREEN}%d{RESET} ", arr[i]);
		return (0);
	}
	else if (((fl == 3 && num == 1) || (fl == 4 && num == 2))
		&& (i == 0 || i == 1))
	{
		if (i == 0)
			ft_printf("{GREEN}%d{RESET} ", arr[i]);
		else if (i == 1)
			ft_printf("{RED}%d{RESET} ", arr[i]);
		return (0);
	}
	return (1);
}

void	print_array(int arr[], int size, int fl, int num)
{
	int i;

	i = -1;
	while (++i < size)
	{
		if (print_arr2(arr, i, fl, num))
		{
			if (((fl == 5 && num == 1) || (fl == 7 && num == 2))
				&& (i == 0 || i == size - 1))
				i == 0 ? ft_printf("{RED}%d{RESET} ", arr[i])
			: ft_printf("{GREEN}%d{RESET} ", arr[i]);
			else if (((fl == 6 && num == 1) || (fl == 8 && num == 2))
				&& (i == 0 || i == size - 1))
				i == 0 ? ft_printf("{GREEN}%d{RESET} ", arr[i])
			: ft_printf("{RED}%d{RESET} ", arr[i]);
			else
				ft_printf("%d ", arr[i]);
		}
	}
}

void	print_stacks(t_stack *stack, int fl)
{
	if (fl)
		ft_printf("\t\t\t");
	ft_printf("Stack A: [ ");
	print_array(stack->st1, stack->num_1, stack->op_fl, 1);
	ft_printf("]\n");
	if (fl)
		ft_printf("\t\t\t");
	ft_printf("Stack B: { ");
	print_array(stack->st2, stack->num_2, stack->op_fl, 2);
	ft_printf("}\n");
	stack->op_fl = 0;
}

void	determ_op_fl(t_stack *stack, char *s)
{
	if (ft_strequ(s, "pa"))
		stack->op_fl = 1;
	else if (ft_strequ(s, "pb"))
		stack->op_fl = 2;
	else if (ft_strequ(s, "sa"))
		stack->op_fl = 3;
	else if (ft_strequ(s, "sb"))
		stack->op_fl = 4;
	else if (ft_strequ(s, "ra"))
		stack->op_fl = 5;
	else if (ft_strequ(s, "rra"))
		stack->op_fl = 6;
	else if (ft_strequ(s, "rb"))
		stack->op_fl = 7;
	else if (ft_strequ(s, "rrb"))
		stack->op_fl = 8;
}
