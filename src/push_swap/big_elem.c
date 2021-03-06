/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_elem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 21:00:16 by akupriia          #+#    #+#             */
/*   Updated: 2019/04/04 22:48:42 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

int		bigger_elem(t_stack *stack)
{
	int i;
	int j;
	int fl;

	j = stack->num_2 - 1;
	fl = 0;
	if (stack->ind < 1)
		return (0);
	while (j > stack->num_2 - 1 - stack->cnt[stack->index - 1])
	{
		i = 0;
		while (i < stack->num_elem[stack->ind - 1])
		{
			if (stack->st2[j] > stack->st2[i++])
			{
				fl = 1;
				break ;
			}
		}
		j--;
	}
	if (if_fl_belem(stack, fl))
		return (1);
	return (0);
}

void	free_stack(t_stack *stack)
{
	free(stack->st1);
	free(stack->st2);
	free(stack);
}

void			ft_error(int code)
{
	if (code == 1)
		ft_printf("{RED}Duplicate number in ./push_swap{RESET}\n");
	else if (code == 2)
		ft_printf("{RED}No arguments, in ./push_swap, man!{RESET}\n");
	else if (code == 3)
		ft_printf("{RED}Wrong number in ./push_swap{RESET}\n");
	exit(1);
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
	stack = ft_memalloc(sizeof(t_stack));
	stack->st1 = malloc(sizeof(int) * (i - 1));
	stack->st2 = malloc(sizeof(int) * (i - 1));
	if (i > 1)
		stack->num_elem = ft_memalloc(sizeof(int) * (i - 1) / 2);
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
