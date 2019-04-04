/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 17:54:44 by akupriia          #+#    #+#             */
/*   Updated: 2019/04/04 23:36:50 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

int				num_cor(char *line, t_stack *stack)
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

void			parse_data(int ac, char **av, t_stack *stack)
{
	int		i;
	int		res;

	i = 0;
	while (++i < ac)
	{
		if ((res = num_cor(av[i], stack)) == 1)
			stack->st1[i - 1] = ft_atoi(av[i]);
		else if (res == -1)
			ft_error(1);
		else
			ft_error(3);
		stack->num_1++;
	}
}

int				recur_ops(char *a, char *b)
{
	if ((ft_strequ(a, op_list->content) && ft_strequ(b,
		op_list->next->content)) || (ft_strequ(b, op_list->content)
		&& ft_strequ(a, op_list->next->content)))
		return (1);
	else
		return (0);
}

void			change_op_list(char c, int ind)
{
	t_list *tmp_list;

	((char *)op_list->content)[ind] = c;
	tmp_list = (op_list->next)->next;
	free(op_list->next->content);
	free(op_list->next);
	op_list->next = tmp_list;
	op_list = op_list->next;
}

static void		print_change_ops(void)
{
	int			i;
	t_list		*tmp_list;
/*
**	const char	*ops[] = {"sa", "sb", "ra", "rb", "rra", "rrb"};
*/

	tmp_list = op_list;
	while (op_list && !(i = 0))
	{
/*		does not substitute operations anyway, cos I don't have recurring operations because of some reason
**	
**	 	while ((i += 2) && i < 6)
**			if (recur_ops((char *)ops[i], (char *)ops[i + 1]))
**				change_op_list(ops[i][0], ft_strlen(ops[i]) - 1);
*/	
		ft_printf("%s", op_list->content);
		// free(op_list->content);
		op_list = op_list->next;
	}
	op_list = tmp_list;
}

int				main(int ac, char **av)
{
	t_stack	*stack;

	if (ac == 1)
		ft_error(2);
	stack = ft_memalloc(sizeof(t_stack));
	op_list = ft_memalloc(sizeof(t_list));
	stack->st1 = ft_memalloc(sizeof(int) * (ac - 1));
	stack->st2 = ft_memalloc(sizeof(int) * (ac - 1));
	if (ac > 2)
		stack->num_elem = ft_memalloc(sizeof(int) * (ac - 1) / 2);
	if (ac == 2)
		stack = check_if_str(av[1], stack);
	else
		parse_data(ac, av, stack);
	ps_sort(stack);
	print_change_ops();
	return (0);
}
