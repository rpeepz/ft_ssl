/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_to_buf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 04:23:11 by rpapagna          #+#    #+#             */
/*   Updated: 2019/06/20 05:02:01 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static void		pos_justify(char *buf, t_mod mod, int len)
{
	int		nbyte;

	nbyte = 0;
	mod.neg = mod.fl.fplus;
	nbyte = ft_padding(buf, len, mod, nbyte);
	if (!mod.fl.fplus && mod.fl.space && !nbyte)
	{
		ft_strcpy(buf, " ");
		buf++;
	}
}

static void		right_justify(char *buf, char *num, t_mod mod, int capital)
{
	int		len;
	int		nbyte;

	nbyte = 0;
	if ((len = LEN(num)) && mod.fl.pound && num[0] != '0' && num[0] != '\0')
	{
		if (mod.fl.fzero && mod.prcsn == -1)
		{
			IF_THEN(capital == 8, ft_strcpy(buf, "0x"));
			IF_THEN(capital == 18, ft_strcpy(buf, "0X"));
		}
		pos_justify(buf + LEN(buf), mod, len);
		if (!mod.fl.fzero || mod.prcsn > -1)
		{
			IF_THEN(capital == 8, ft_strcpy(buf, "0x"));
			IF_THEN(capital == 18, ft_strcpy(buf, "0X"));
		}
	}
	else
		pos_justify(buf + LEN(buf), mod, len);
	if (mod.prcsn > len)
		while ((mod.prcsn--) - len > 0)
			ft_strcpy(buf + LEN(buf), "0");
	ft_strncpy(buf + LEN(buf), num, len);
}

static void		left_justify(char *buf, char *num, t_mod mod, int capital)
{
	int		len;
	int		count;

	count = 0;
	len = (int)ft_strlen(num);
	if (mod.fl.pound && num[0] != '0' && num[0] != '\0')
	{
		if (capital == 8)
			ft_strcpy(buf, "0x");
		else
			ft_strcpy(buf, "0X");
		buf += 2;
		count += 2;
	}
	while (mod.prcsn-- > len)
	{
		ft_strcpy(buf, "0");
		buf++;
		count++;
	}
	ADD_TO_BUFF(buf, num, count, len);
	while (count < mod.width)
	{
		ADD_ONE_TO_BUFF(buf, " ", count);
	}
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

int				x_to_buf(char *buf, t_mod modifiers, va_list ap, int i)
{
	int64_t	num;
	char	*str;
	int		len;

	len = -1;
	num = convert_length(modifiers.length, ap);
	if (modifiers.length == 'l' || modifiers.length / 2 == 'l' ||
		modifiers.length == 'z')
		str = num_string_u_base(num, 16);
	else
		str = ft_uitoa_base(num, 16);
	if (i == 8)
		while (str[++len])
			str[len] = ft_tolower(str[len]);
	IF_THEN(str[0] == '0' && modifiers.prcsn == 0, str[0] = '\0');
	if (modifiers.fl.minus == 1)
		left_justify(buf, str, modifiers, i);
	else
		right_justify(buf, str, modifiers, i);
	free(str);
	return (LEN(buf));
}
