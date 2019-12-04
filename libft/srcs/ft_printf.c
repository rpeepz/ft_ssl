/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 22:34:52 by rpapagna          #+#    #+#             */
/*   Updated: 2019/11/01 22:32:33 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
**	Produces output according to a format string passed into funtion.
**	parses and converts variables to output based on conversion symbols
**	as standard logic for basic printf.
*/

static int		dispatch(t_mods modifier, va_list ap, int i)
{
	if (i == 1)
		return (convert_percent(modifier));
	if ((i == 2 || i == 12))
		return (convert_i(modifier, ap));
	if (i == 3)
		return (convert_c(modifier, ap));
	if (i == 4)
		return (convert_s(modifier, ap));
	if (i == 5)
		return (convert_p(modifier, ap));
	if ((i == 6 || i == 16))
		return (convert_o(modifier, ap, i));
	if ((i == 7 || i == 17))
		return (convert_u(modifier, ap, i));
	if ((i == 8 || i == 18))
		return (convert_x(modifier, ap, i));
	if ((i == 9 || i == 19))
		return (convert_f(modifier, ap, i));
	if ((i == 10 || i == 20))
		return (convert_b(modifier, ap, i));
	return (42);
}

static int		parse_string(char **str, va_list ap)
{
	int		i;
	t_mods	modifier;

	(*str)++;
	if (**str)
		modifier = get_mods(str, ap);
	if (!(i = get_type_specifier(**str)))
	{
		if (**str && (i = 1))
			print_one(str);
		return (i);
	}
	(*str)++;
	return (dispatch(modifier, ap, i));
}

int				ft_printf(char *str, ...)
{
	int		nbyte;
	va_list	ap;

	nbyte = 0;
	va_start(ap, str);
	while (*str)
	{
		if (*str != '%')
		{
			print_one(&str);
			nbyte++;
		}
		else
		{
			nbyte += parse_string(&str, ap);
		}
	}
	va_end(ap);
	if (nbyte < 0)
		nbyte = 0;
	return (nbyte);
}
