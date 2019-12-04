/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_to_buf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 01:49:14 by rpapagna          #+#    #+#             */
/*   Updated: 2019/11/01 22:14:20 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_sprintf.h"

static int	right_justify(char *buf, char *s, int len, t_mod mod)
{
	int		nbyte;

	nbyte = 0;
	if (mod.fl.fzero == 1)
	{
		while (mod.width-- > len)
		{
			add_one_to_buf(&buf, '0', &nbyte);
		}
	}
	else
	{
		while (mod.width-- > len)
		{
			add_one_to_buf(&buf, ' ', &nbyte);
		}
	}
	add_to_buf(&buf, s, &nbyte, len);
	return (nbyte);
}

static int	left_justify(char *buf, char *s, int len, t_mod mod)
{
	int		nbyte;

	nbyte = 0;
	add_to_buf(&buf, s, &nbyte, len);
	while (nbyte < mod.width)
	{
		add_one_to_buf(&buf, ' ', &nbyte);
	}
	return (nbyte);
}

int			s_to_buf(char *buf, t_mod modifiers, va_list ap)
{
	char	*s;
	char	*s2;
	int		len;

	s = va_arg(ap, char *);
	!s ? s = "(null)" : 0;
	if (modifiers.prcsn >= 0 && modifiers.prcsn < (int)ft_strlen(s))
		s2 = ft_strndup(s, modifiers.prcsn);
	else
		s2 = ft_strdup(s);
	if ((len = ft_strlen(s2)) && modifiers.fl.minus == 1)
	{
		if (modifiers.width <= len)
			ft_strcpy(buf, s2);
		else
			left_justify(buf, s2, len, modifiers);
		free(s2);
		return (modifiers.width <= len ? len : modifiers.width);
	}
	if (modifiers.width > len)
		right_justify(buf, s2, len, modifiers);
	else
		ft_strcpy(buf, s2);
	free(s2);
	return (modifiers.width > len ? modifiers.width : len);
}
