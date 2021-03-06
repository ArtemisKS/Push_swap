/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpush.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 20:39:35 by akupriia          #+#    #+#             */
/*   Updated: 2019/04/04 23:17:25 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpush(t_list **alst, t_list *new)
{
	t_list	*lst;
	int		i;

	i = 0;
	if (!alst || !new)
		return ;
	lst = *alst;
	while (lst && lst->content && (++i > 0))
		lst = lst->next;
	if (i)
	{
		lst = *alst;
		while (lst->next)
			lst = lst->next;
		lst->next = new;
	}
	else
	{
		free(*alst);
		*alst = new;
	}
}
