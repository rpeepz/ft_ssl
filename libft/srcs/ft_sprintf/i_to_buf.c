/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_to_buf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 23:12:09 by rpapagna          #+#    #+#             */
/*   Updated: 2019/11/01 22:14:16 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_sprintf.h"

static void		pos_justify(char *buf, t_mod mod, int len)
{
	int		nbyte;

	nbyte = 0;
	if (mod.fl.fplus && mod.fl.fzero && mod.prcsn < 0 &&
		mod.width > len && (mod.fl.space = -1))
	{
		ft_strcpy(buf, "+");
		buf++;
		nbyte++;
	}
	mod.neg = mod.fl.fplus;
	nbyte = ft_padding(buf, len, mod, nbyte);
	if ((mod.fl.fplus && mod.fl.space != -1))
	{
		ft_strcpy(buf, "+");
		buf++;
		nbyte++;
	}
	if (!mod.fl.fplus && mod.fl.space && !nbyte)
	{
		ft_strcpy(buf, " ");
		buf++;
	}
}

static void		neg_justify(char *buf, t_mod mod, char *num)
{
	int		nbyte;

	nbyte = 0;
	if (mod.fl.fzero && mod.prcsn < 0 && mod.width > (int)ft_strlen(num))
	{
		ft_strcpy(buf, "-");
		buf++;
		nbyte++;
	}
	nbyte = ft_padding(buf, ft_strlen(num), mod, nbyte);
	if (!mod.fl.fzero || mod.prcsn > 0 || !nbyte)
	{
		ft_strcpy(buf, "-");
		buf++;
	}
}

static void		right_justify(char *buf, char *num, t_mod mod, int nbyte)
{
	int		len;

	if (mod.neg == 1)
		neg_justify(buf, mod, num);
	else if (mod.neg == 0)
		pos_justify(buf, mod, ft_strlen(num));
	if (mod.prcsn > (len = ft_strlen(num)))
	{
		while ((mod.prcsn--) - len > 0)
		{
			ft_strcpy(buf, "0");
			buf++;
		}
	}
	nbyte = ft_strlen(buf);
	ft_strncpy(buf + nbyte, num, len);
}

static int64_t	convert_length(int length, va_list ap)
{
	int64_t		d;

	if (length == 'h')
	{
		d = va_arg(ap, int);
		return ((short)d);
	}
	else if (length / 2 == 'h')
	{
		d = va_arg(ap, int);
		return ((signed char)d);
	}
	else if (length == 'l')
		d = va_arg(ap, long);
	else if (length / 2 == 'l' || length == 'z')
		d = va_arg(ap, long long);
	else
		d = va_arg(ap, int);
	return (d);
}

int				i_to_buf(char *buf, t_mod modifiers, va_list ap)
{
	int64_t	num;
	char	*str;

	num = convert_length(modifiers.length, ap);
	modifiers.neg = (num < 0) ? 1 : 0;
	modifiers.neg == 1 ? num *= -1 : 0;
	str = num_string_base(num, 10);
	str[0] == '0' && modifiers.prcsn == 0 ? str[0] = '\0' : 0;
	if (modifiers.fl.minus == 1)
		left_jut(buf, str, modifiers, 0);
	else
		right_justify(buf, str, modifiers, 0);
	free(str);
	return (ft_strlen(buf));
}
