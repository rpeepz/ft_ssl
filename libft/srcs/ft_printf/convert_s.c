/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 20:59:06 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/26 16:35:36 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/*
**	s	The char* argument is expected to be a pointer to an array of character
**		type (pointer to a string).
**		Characters from the array are written up to (but not including) a
**		terminating NULL character; if a precision is specified, no more than
**		the number specified are written.
**		If a precision is given, no null character need be present;
**		if the precision is not specified, or is greater than the size of the
**		array, the array must contain a terminating NUL character.
*/

static int	left_justify(t_mods mod, char *s, int len)
{
	int		nbyte;

	nbyte = 0;
	nbyte += (int)write(1, s, len);
	while (nbyte < mod.width)
		nbyte += (int)write(1, " ", 1);
	return (nbyte);
}

static int	right_justify(t_mods mod, char *s, int len)
{
	int		nbyte;

	nbyte = 0;
	if (mod.fl.fzero == 1)
	{
		while (mod.width-- > len)
			nbyte += (int)write(1, "0", 1);
	}
	else
	{
		while (mod.width-- > len)
			nbyte += (int)write(1, " ", 1);
	}
	return (nbyte += (int)write(1, s, len));
}

int			convert_s(t_mods modifiers, va_list ap)
{
	char	*s;
	char	*s2;
	int		nbyte;
	int		len;

	s = va_arg(ap, char *);
	IF_THEN(!s, s = "(null)");
	nbyte = 0;
	if (modifiers.prcsn >= 0 && modifiers.prcsn < (int)ft_strlen(s))
		s2 = ft_strndup(s, modifiers.prcsn);
	else
		s2 = ft_strdup(s);
	if ((len = LEN(s2)) && modifiers.fl.minus == 1)
	{
		if (modifiers.width <= len)
			nbyte += (int)write(1, s2, len);
		else
			nbyte += left_justify(modifiers, s2, len);
		IF_RETURN(1, (ft_pipewrench("-s", s2) + nbyte) - 1);
	}
	if (modifiers.width > len)
		nbyte += right_justify(modifiers, s2, len);
	else
		nbyte += (int)write(1, s2, len);
	IF_RETURN(1, (ft_pipewrench("-s", s2) + nbyte) - 1);
}
