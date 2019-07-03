/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 22:34:52 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/26 16:31:39 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*
**	Produces output according to a format string passed into funtion.
**	parses and converts variables to output based on conversion symbols
**	as standard logic for basic printf.
*/

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
	IF_RETURN(i == 1 && (*str)++, convert_percent(modifier));
	IF_RETURN((i == 2 || i == 12) && (*str)++, convert_i(modifier, ap));
	IF_RETURN(i == 3 && (*str)++, convert_c(modifier, ap));
	IF_RETURN(i == 4 && (*str)++, convert_s(modifier, ap));
	IF_RETURN(i == 5 && (*str)++, convert_p(modifier, ap));
	IF_RETURN((i == 6 || i == 16) && (*str)++, convert_o(modifier, ap, i));
	IF_RETURN((i == 7 || i == 17) && (*str)++, convert_u(modifier, ap, i));
	IF_RETURN((i == 8 || i == 18) && (*str)++, convert_x(modifier, ap, i));
	IF_RETURN((i == 9 || i == 19) && (*str)++, convert_f(modifier, ap, i));
	IF_RETURN((i == 10 || i == 20) && (*str)++, convert_b(modifier, ap, i));
	return (42);
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
	IF_THEN(nbyte < 0, nbyte = 0);
	return (nbyte);
}
