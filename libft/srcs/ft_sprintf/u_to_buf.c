/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_to_buf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 19:44:34 by rpapagna          #+#    #+#             */
/*   Updated: 2019/11/03 19:44:36 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_sprintf.h"

static void		left_just(char *buf, char *num, t_mod mod, int nbyte)
{
	int		len;

	len = (int)ft_strlen(num);
	while (mod.prcsn-- > len)
	{
		ft_strcpy(buf, "0");
		buf++;
	}
	ADD_TO_BUFF(buf, num, nbyte, len);
	while (nbyte < mod.width)
	{
		ADD_ONE_TO_BUFF(buf, " ", nbyte);
	}
}

static void		pos_justify(char *buf, t_mod mod, int len)
{
	int		nbyte;

	nbyte = 0;
	mod.neg = mod.fl.fplus;
	nbyte = ft_padding(buf, len, mod, nbyte);
	if (mod.fl.space && !nbyte)
	{
		ft_strcpy(buf, " ");
		buf++;
	}
}

static void		right_justify(char *buf, char *num, t_mod mod, int nbyte)
{
	int		len;

	if (mod.neg == 0)
		pos_justify(buf, mod, LEN(num));
	if (mod.prcsn > (len = LEN(num)))
	{
		while ((mod.prcsn--) - len > 0)
		{
			ft_strcpy(buf, "0");
			buf++;
		}
	}
	nbyte = LEN(buf);
	ft_strncpy(buf + nbyte, num, len);
}

static uint64_t	convert_length(int length, va_list ap)
{
	uint64_t		u;

	if (length == 'h')
	{
		u = va_arg(ap, int);
		return ((unsigned short)u);
	}
	else if (length / 2 == 'h')
	{
		u = va_arg(ap, int);
		return ((unsigned char)u);
	}
	else if (length == 'l')
		u = va_arg(ap, unsigned long);
	else if (length / 2 == 'l' || length == 'z')
		u = va_arg(ap, unsigned long long);
	else
		u = va_arg(ap, unsigned int);
	return (u);
}

int				u_to_buf(char *buf, t_mod modifiers, va_list ap, int i)
{
	uint64_t	num;
	char		*str;

	if (i == 17)
		modifiers.length = 'z';
	num = convert_length(modifiers.length, ap);
	str = num_string_u_base(num, 10);
	IF_THEN(str[0] == '0' && modifiers.prcsn == 0, str[0] = '\0');
	if (modifiers.fl.minus == 1)
		left_just(buf, str, modifiers, 0);
	else
		right_justify(buf, str, modifiers, 0);
	free(str);
	return (LEN(buf));
}
