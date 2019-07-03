/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 21:07:17 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/26 16:35:36 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int		is_flag(char x)
{
	return (x == ' ' || x == '#' || x == '+' || x == '-' || x == '0');
}

int		get_undef_length(char x)
{
	if (x == 'z' || x == 'j')
		return (1);
	if (x == 'h' || x == 'l')
		return (2);
	return (0);
}

int		get_type_specifier(char x)
{
	char	*str;
	int		i;

	i = -1;
	str = "%dcspouxfb";
	while (str[++i])
		if (x == str[i])
			return (i + 1);
	str = ".i...OUXFB";
	while (--i >= 0)
		if (x == str[i])
			return (i + 11);
	return (0);
}
/*
**	below find old version revised with help of jmbomeyo
**
**	int		get_type_specifier(char x)
**	{
**	if (x == '%')
**		return (1);
**	else if (x == 'd' || x == 'i')
**		return (2);
**	else if (x == 'c')
**		return (3);
**	else if (x == 's')
**		return (4);
**	else if (x == 'p')
**		return (5);
**	else if (x == 'o')
**		return (6);
**	else if (x == 'u')
**		return (7);
**	else if (x == 'x' || x == 'X')
**		return (8);
**	else if (x == 'f' || x == 'F')
**		return (9);
**	else if (x == 'k' || x == 'K')
**		return (10);
**	else if (x == '?')
**		return (11);
**	return (0);
**	}
**
** will try to incorporate the ability
** to print a timestamp using 'k' and 'K'
** and possibly mods for formatting
*/
