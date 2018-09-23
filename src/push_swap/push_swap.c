/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 17:54:44 by akupriia          #+#    #+#             */
/*   Updated: 2018/09/23 20:50:02 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

int		num_cor(char *line, t_stack *stack)
{
	int		i;
	char	*s;

	i = -1;
	if (!(int_value(line)))
		return (0);
	while (line[++i])
		if (!(ft_isdigit(line[i])) && (!(line[i] == '-')))
			return (0);
	i = 0;
	while (i < stack->num_1)
	{
		s = ft_itoa(stack->st1[i++]);
		if (ft_strequ(s, line))
		{
			ft_strdel(&s);
			return (-1);
		}
		ft_strdel(&s);
	}
	s = ft_itoa(ft_atoi(line));
	if (!ft_strequ(s, line))
		return (0);
	ft_strdel(&s);
	return (1);
}

void	ft_error(int code)
{
	if (code == 1)
		ft_printf("{RED}Duplicate number in ./push_swap{RESET}\n");
	else if (code == 2)
		ft_printf("{RED}No arguments, in ./push_swap, man!{RESET}\n");
	else if (code == 3)
		ft_printf("{RED}Wrong number in ./push_swap{RESET}\n");
	// system("leaks -q push_swap");
	exit(1);
}

t_stack	*init_stack(int ac)
{
	t_stack	*stack;
	int		i;

	i = 0;
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
	stack->fl = 0;
	while (i < 100)
		stack->cnt[i++] = 0;
	stack->index = 0;
	stack->in = 0;
	return (stack);
}

void	parse_data(int ac, char **av, t_stack *stack)
{
	int		i;
	int		res;

	i = 1;
	while (i < ac)
	{
		if ((res = num_cor(av[i], stack)) == 1)
			stack->st1[i - 1] = ft_atoi(av[i]);
		else if (res == -1)
			ft_error(1);
		else
			ft_error(3);
		stack->num_1++;
		i++;
	}
}

int		main(int ac, char **av)
{
	t_stack *stack;

	if (ac == 1)
		ft_error(2);
	stack = init_stack(ac);
	if (ac == 2)
		stack = check_if_str(av[1], stack);
	else
		parse_data(ac, av, stack);
	ps_sort(stack);
	// system("leaks -q push_swap");
	return (0);
}
