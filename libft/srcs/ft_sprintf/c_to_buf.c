/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_to_buf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 01:39:09 by rpapagna          #+#    #+#             */
/*   Updated: 2019/11/01 22:13:57 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_sprintf.h"

static int		left_justify(char *buf, char c, int width)
{
	int		n;

	n = 0;
	add_one_to_buf(&buf, c, &n);
	if (n < width)
		while (n < width)
		{
			add_one_to_buf(&buf, ' ', &n);
		}
	return (n);
}

static int		right_justify(char *buf, char c, int width, int fzero)
{
	int		n;

	n = 0;
	if (fzero)
	{
		while (width-- > 1)
		{
			add_one_to_buf(&buf, '0', &n);
		}
	}
	else
	{
		while (width-- > 1)
		{
			add_one_to_buf(&buf, ' ', &n);
		}
	}
	add_one_to_buf(&buf, c, &n);
	return (n);
}

int				c_to_buf(char *buf, t_mod modifiers, va_list ap)
{
	char	c;
	int		n;

	c = va_arg(ap, int);
	if (modifiers.fl.minus == 1)
	{
		return (left_justify(buf, c, modifiers.width));
	}
	if (modifiers.width > 1)
	{
		return (right_justify(buf, c, modifiers.width, modifiers.fl.fzero));
	}
	n = 0;
	add_one_to_buf(&buf, c, &n);
	return (n);
}
