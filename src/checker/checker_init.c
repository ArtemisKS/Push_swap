/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 22:58:54 by akupriia          #+#    #+#             */
/*   Updated: 2018/09/23 20:50:02 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

t_stack	*init_stack1(int ac)
{
	t_stack *stack;

	if (ac == 1)
		ft_error(2);
	stack = (t_stack*)malloc(sizeof(t_stack));
	stack->st1 = (int*)malloc(sizeof(int) * (ac - 1));
	stack->st2 = (int*)malloc(sizeof(int) * (ac - 1));
	if (ac > 2)
	{
		stack->num_elem = (int*)malloc(sizeof(int) * (ac - 1) / 2);
		init_numelem(stack, (ac - 1) / 2);
	}
	stack->num_1 = 0;
	stack->num_2 = 0;
	stack->ind = 0;
	stack->sum_elem = 0;
	stack->sort_elem = 0;
	stack->el_num = 0;
	stack->debug = 0;
	stack->visual = 0;
	stack->man = 0;
	stack->color = 0;
	stack->fl = 0;
	return (stack);
}

t_stack	*main_ifs(int ac, char **av, t_stack *stack)
{
	if (ac == 2)
		stack = check_if_str(av[1], stack);
	else
	{
		if (ft_strequ(av[1], "-d"))
			stack->debug = 1;
		if (ft_strequ(av[1], "-v"))
		{
			stack->visual = 1;
			stack->color = 1;
		}
		else if (ft_strequ(av[1], "-m"))
		{
			stack->man = 1;
			stack->color = 1;
		}
		else if (ft_strequ(av[2], "-c"))
			stack->color = 1;
		parse_data(ac, av, stack);
	}
	return (stack);
}

void	ternar_func(t_stack *stack, const long int time)
{
	int	j;

	j = 0;
	while (j < time / stack->el_num)
		j++;
}

void	check_conds(t_stack *stack, const t_oper arr[], int i, int cnt)
{
	const long int	time = 2000000000;

	if (stack->debug)
	{
		ft_printf("%s\n", arr[i].oper);
		if (stack->color)
			determ_op_fl(stack, arr[i].oper);
		print_stacks(stack, 0);
	}
	else if (stack->visual || stack->man)
	{
		ft_printf("\n\n\t\t\t%s\n", arr[i].oper);
		if (stack->color)
			determ_op_fl(stack, arr[i].oper);
		print_stacks(stack, 1);
		stack->man == 0 ? ternar_func(stack, time) : read(1, 0, 1);
		if (!is_sorted(stack) || stack->num_2)
			system("clear");
		else
			ft_printf("Total number of operations: {GREEN}%d{RESET}\n", cnt);
	}
}

void	check(char *s, t_stack *stack)
{
	int				i;
	static int		cnt = 0;
	const t_oper	arr[] = {{"pa", &pa1}, {"pb", &pb1}, {"sa", &sa1}, \
	{"sb", &sb1}, {"ra", &ra1}, {"rra", &rra1}, {"rb", &rb1}, {"rrb", &rrb1}, \
	{"rr", &rr}, {"ss", &ss}, {"rrr", &rrr}};

	i = 0;
	while (i < 11)
	{
		if (ft_strequ(s, arr[i].oper))
		{
			arr[i].func(stack);
			cnt++;
			check_conds(stack, arr, i, cnt);
			break ;
		}
		i++;
	}
	if (i == 11)
		ft_error(4);
}
