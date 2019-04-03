/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 22:58:54 by akupriia          #+#    #+#             */
/*   Updated: 2019/04/02 20:39:34 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

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

	i = -1;
	while (++i < 11)
		if (ft_strequ(s, arr[i].oper))
		{
			arr[i].func(stack);
			cnt++;
			check_conds(stack, arr, i, cnt);
			break ;
		}
	if (i == 11)
		ft_error(4);
}
