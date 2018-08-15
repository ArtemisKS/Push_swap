/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 19:52:27 by akupriia          #+#    #+#             */
/*   Updated: 2018/07/23 21:24:08 by akupriia         ###   ########.fr       */
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

void	ft_error(int code)
{
	if (code == 1)
		ft_printf("{RED}Duplicate number in ./checker{RESET}\n");
	else if (code == 2)
		ft_printf("{RED}No arguments in ./checker, man!{RESET}\n");
	else if (code == 3)
		ft_printf("{RED}Wrong number in ./checker{RESET}\n");
	else if (code == 4)
		ft_printf("{RED}Wrong operation passed to ./checker{RESET}\n");
	else if (code == 5)
		ft_printf("{RED}Array is unsorted in ./checker{RESET}\n");
	system("leaks -q checker");
	exit(1);
}

int		main(int ac, char **av)
{
	char	*s;
	int		gnl;
	int		i;
	t_stack	*stack;

	s = NULL;
	i = 0;
	stack = init_stack1(ac);
	stack = main_ifs(ac, av, stack);
	while (((gnl = get_next_line(0, &s)) > 0) && (++i))
	{
		check(s, stack);
		ft_strdel(&s);
	}
	if ((gnl < 0 || !i) && (!is_sorted(stack)))
		ft_error(5);
	ft_strdel(&s);
	if (is_sorted(stack) && !stack->num_2)
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
	return (0);
}
