/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 20:51:06 by akupriia          #+#    #+#             */
/*   Updated: 2017/12/26 20:51:07 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int			color_func(const char **colors, char *s, int *fl)
{
	int i;

	i = 0;
	while (colors[i])
	{
		if (ft_strstr_start(s, colors[i]))
		{
			*fl = 1;
			break ;
		}
		i++;
	}
	return (i);
}

char		*check_for_colors(char *fmt, int *fl, int ind)
{
	const char	*colors[] = {"{RED}", "{RESET}", "{BROWN}", "{LRED}",
	"{GREEN}", "{YELLOW}", "{BLUE}", "{MAGENTA}", "{CYAN}", "{WHITE}", NULL};
	const char	*col[] = {"\033[31;1m", "\033[0m", "\033[22;33m",
	"\033[01;31m", "\033[32;1m", "\033[33;1m", "\033[01;34m",
	"\033[35;1m", "\033[36;1m", "\033[37;1m", NULL};
	char		*s;
	int			i;

	s = &fmt[ind];
	i = color_func(colors, s, fl);
	if (*fl)
	{
		s += ft_strlen(colors[i]);
		write(1, col[i], ft_strlen(col[i]));
		fmt = s;
	}
	return (fmt);
}

static int	do_cycle(va_list ap, char **fmt, int *i, t_spec *ts)
{
	static int	j = 0;
	int			fl;

	fl = 0;
	*fmt = check_for_colors(*fmt, &fl, *i);
	if (fl)
		*i = 0;
	if ((*fmt)[*i] == '%' && (*fmt)[*i + 1])
	{
		(*i)++;
		*i += parse_spec(&((*fmt)[*i]), ts, ap);
		j = output_fstring(ap, (*fmt)[*i], j, ts);
	}
	else if ((*fmt)[*i] != '%')
	{
		write(1, &((*fmt)[*i]), 1);
		j++;
	}
	(*i)++;
	return (j);
}

int			parse_format(va_list ap, char *fmt)
{
	int		i;
	int		j;
	t_spec	*ts;

	i = 0;
	j = 0;
	ts = (t_spec *)malloc(sizeof(t_spec));
	while (fmt[i])
		j = do_cycle(ap, &fmt, &i, ts);
	ft_memdel((void**)&ts);
	return (j);
}

int			ft_printf(char *fmt, ...)
{
	va_list	ap;
	int		n;

	va_start(ap, fmt);
	n = parse_format(ap, fmt);
	va_end(ap);
	return (n);
}
