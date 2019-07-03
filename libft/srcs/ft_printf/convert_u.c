/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 21:04:01 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/26 16:35:36 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/*
**	u, U	The int (or variant) argument is converted to unsigned decimal.
**			The precision, if any, gives the minimum number of digits
**			that must appear; if the converted value requires fewer digits,
**			it is padded on the left with zeros.
*/

static int		pad_width(t_mods mod, int len, int nbyte, int neg)
{
	char	*pad_char;

	pad_char = " ";
	if (len > mod.prcsn || mod.prcsn == -1)
	{
		if (mod.width > len)
		{
			IF_THEN(mod.fl.fzero && mod.prcsn == -1, pad_char = "0");
			if (nbyte == 0)
			{
				while (mod.width - len - neg > nbyte)
					nbyte += (int)write(1, pad_char, 1);
			}
			else
				while (mod.width - len > nbyte)
					nbyte += (int)write(1, pad_char, 1);
		}
	}
	else
		while (mod.width - mod.prcsn - neg > nbyte)
			nbyte += (int)write(1, pad_char, 1);
	return (nbyte);
}

static	int		right_justify(t_mods mod, char *num, int nbyte)
{
	int		len;

	len = (int)ft_strlen(num);
	nbyte = pad_width(mod, len, nbyte, mod.fl.fplus);
	if (mod.prcsn > len)
		while ((mod.prcsn--) - len > 0)
			nbyte += (int)write(1, "0", 1);
	return (nbyte += (int)write(1, num, len));
}

static	int		left_justify(t_mods mod, char *num, int nbyte)
{
	int		len;

	len = (int)ft_strlen(num);
	while (mod.prcsn-- > len)
		nbyte += (int)write(1, "0", 1);
	nbyte += (int)write(1, num, len);
	while (nbyte < mod.width)
		nbyte += (int)write(1, " ", 1);
	return (nbyte);
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
		u = va_arg(ap, int);
	return (u);
}

int				convert_u(t_mods modifiers, va_list ap, int i)
{
	uint64_t	num;
	int			nbyte;
	char		*str;

	nbyte = 0;
	if (i == 17)
		modifiers.length = 'z';
	num = convert_length(modifiers.length, ap);
	if (modifiers.length == 'l' || modifiers.length / 2 == 'l' ||
		modifiers.length == 'z')
		str = num_string_u_base(num, 10);
	else
		str = ft_uitoa_base(num, 10);
	IF_THEN(str[0] == '0' && modifiers.prcsn == 0, str[0] = '\0');
	if (modifiers.fl.minus == 1)
		nbyte += left_justify(modifiers, str, nbyte);
	else
		nbyte += right_justify(modifiers, str, nbyte);
	if (str)
		free(str);
	return (nbyte);
}
