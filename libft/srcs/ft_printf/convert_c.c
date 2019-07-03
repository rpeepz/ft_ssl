/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 18:52:45 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/26 16:35:36 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/*
**	c	The int argument is converted to an unsigned char
**		and the resulting character is written.
*/

static int		left_justify(int width, unsigned char c)
{
	int		n;

	n = (int)write(1, &c, 1);
	if (n < width)
		while (n < width)
			n += (int)write(1, " ", 1);
	return (n);
}

static int		right_justify(int width, int fzero, unsigned char c)
{
	int		n;

	n = 0;
	if (fzero)
	{
		while (width-- > 1)
			n += (int)write(1, "0", 1);
	}
	else
	{
		while (width-- > 1)
			n += (int)write(1, " ", 1);
	}
	n += (int)write(1, &c, 1);
	return (n);
}

int				convert_c(t_mods modifiers, va_list ap)
{
	unsigned char	c;

	c = va_arg(ap, int);
	if (modifiers.fl.minus == 1)
	{
		return (left_justify(modifiers.width, c));
	}
	if (modifiers.width > 1)
	{
		return (right_justify(modifiers.width, modifiers.fl.fzero, c));
	}
	return ((int)write(1, &c, 1));
}
