/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_percent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 19:39:16 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/26 16:35:36 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/*
**	%	A `%' is written.  No argument is converted.
**		The complete conversion specification is `%%'.
*/

static int		left_justify(int width)
{
	int		n;

	n = (int)write(1, "%", 1);
	if (n < width)
		while (n < width)
			n += (int)write(1, " ", 1);
	return (n);
}

static int		right_justify(int width, int fzero)
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
	n += (int)write(1, "%", 1);
	return (n);
}

int				convert_percent(t_mods modifiers)
{
	if (modifiers.fl.minus == 1)
	{
		return (left_justify(modifiers.width));
	}
	if (modifiers.width > 1)
	{
		return (right_justify(modifiers.width, modifiers.fl.fzero));
	}
	return ((int)write(1, "%", 1));
}
