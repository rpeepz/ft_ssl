/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_o.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 20:59:54 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/26 16:35:36 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/*
**	o, O	The int (or variant) argument is converted to unsigned octal.
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
				if (mod.fl.space && mod.fl.fzero)
					nbyte += write(1, " ", 1);
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
	if (mod.fl.fplus)
		nbyte += (int)write(1, "+", 1);
	else if (mod.fl.space)
		nbyte += (int)write(1, " ", 1);
	while (mod.prcsn-- > len)
		nbyte += (int)write(1, "0", 1);
	nbyte += (int)write(1, num, len);
	while (nbyte < mod.width)
		nbyte += (int)write(1, " ", 1);
	return (nbyte);
}

static uint64_t	convert_length(int length, va_list ap)
{
	uint64_t		o;

	if (length == 'h')
	{
		o = va_arg(ap, int);
		return ((unsigned short)o);
	}
	else if (length / 2 == 'h')
	{
		o = va_arg(ap, int);
		return ((unsigned char)o);
	}
	else if (length == 'l')
		o = va_arg(ap, unsigned long);
	else if (length / 2 == 'l' || length == 'z')
		o = va_arg(ap, unsigned long long);
	else
		o = va_arg(ap, int);
	return (o);
}

int				convert_o(t_mods modifiers, va_list ap, int i)
{
	uint64_t	num;
	int			nbyte;
	char		*tmp;
	char		*str;

	nbyte = 0;
	IF_THEN(i == 16, modifiers.length = 'z');
	num = convert_length(modifiers.length, ap);
	if (modifiers.length == 'l' || modifiers.length / 2 == 'l' ||
		modifiers.length == 'z')
		tmp = num_string_u_base(num, 8);
	else
		tmp = ft_uitoa_base(num, 8);
	if (modifiers.fl.pound && tmp[0] != '0')
		str = ft_strjoin("0", tmp);
	else
		str = ft_strdup(tmp);
	free(tmp);
	IF_THEN(str[0] == '0' && modifiers.prcsn == 0 && !modifiers.fl.pound,
			str[0] = '\0');
	if (modifiers.fl.minus == 1)
		nbyte += left_justify(modifiers, str, nbyte);
	else
		nbyte += right_justify(modifiers, str, nbyte);
	IF_RETURN(1, (ft_pipewrench("-s", str) + nbyte) - 1);
}
