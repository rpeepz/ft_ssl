/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_f.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 19:04:29 by rpapagna          #+#    #+#             */
/*   Updated: 2019/11/01 23:23:19 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

/*
**  f, F    The double argument is rounded and converted to decimal notation in
**          the style [-]ddd.ddd, where the number of digits after the
**          decimal-point character is equal to the precision specification.
**          If the precision is missing, it is taken as 6; if the precision is
**          explicitly zero, no decimal-point character appears.
**          If a decimal point appears, at least one digit appears before it.
*/

static int		pad_width(t_mods mod, int len, int nbyte, int neg)
{
	char	*pad_char;

	pad_char = " ";
	if (len > mod.prcsn || mod.prcsn == -1)
	{
		if (mod.width > len)
		{
			mod.fl.fzero && mod.prcsn == -1 ? pad_char = "0" : 0;
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

static	int		right_justify(t_mods m, char *num, int by, int neg)
{
	int		len;

	(len = ft_strlen(num)) && m.fl.pound && !ft_strchr(num, '.') ? len++ : 0;
	if (neg == 1)
	{
		if (m.fl.fzero && m.prcsn < 0 && m.width > len)
			by += write(1, "-", 1);
		by = pad_width(m, len, by, neg);
		(!m.fl.fzero || m.prcsn > 0 || !by) ? by += write(1, "-", 1) : 0;
	}
	else if (neg == 0)
	{
		(m.fl.fplus && m.fl.fzero && m.prcsn < 0 && m.width > len
			&& (m.fl.space = -1)) ? by += write(1, "+", 1) : 0;
		by = pad_width(m, len, by, m.fl.fplus);
		(m.fl.fplus && m.fl.space != -1) ? by += write(1, "+", 1) : 0;
		(!m.fl.fplus && m.fl.space && !by) ? by += write(1, " ", 1) : 0;
	}
	if (m.prcsn > len)
		while ((m.prcsn--) - len > 0)
			by += write(1, "0", 1);
	if (m.fl.pound && !ft_strchr(num, '.'))
		return (by += (write(1, num, len - 1) + write(1, ".", 1)));
	else
		return (by += write(1, num, len));
}

static	int		left_justify(t_mods mod, char *num, int nbyte, int neg)
{
	int		len;

	len = ft_strlen(num);
	mod.fl.pound && mod.prcsn == 0 ? len += 1 : 0;
	if (neg == 1)
		nbyte += (int)write(1, "-", 1);
	else if (neg == 0)
	{
		if (mod.fl.fplus)
			nbyte += (int)write(1, "+", 1);
		else if (mod.fl.space)
			nbyte += (int)write(1, " ", 1);
	}
	while (mod.prcsn-- > len)
		nbyte += (int)write(1, "0", 1);
	if (mod.fl.pound && mod.prcsn == 0)
		if (nbyte += (int)write(1, num, len - 1))
			nbyte += (int)write(1, ".", 1);
	if (!mod.fl.pound && mod.prcsn == 0)
		nbyte += (int)write(1, num, len);
	while (nbyte < mod.width)
		nbyte += (int)write(1, " ", 1);
	return (nbyte);
}

static char		**num_string_modld(long double num, t_mods mod, int add_zeros)
{
	char			**str;
	long double		tmp;
	char			*zeros;
	int				len;

	mod.prcsn == -1 ? mod.prcsn = 6 : 0;
	str = (char **)malloc(sizeof(*str) * 3);
	str[0] = num_string_base(get_pre_float(num, 0), 10);
	str[2] = 0;
	if (mod.prcsn == 0 && (str[1] = ft_strdup("\0")))
		return (str);
	tmp = num - (int)num;
	add_zeros = mod.prcsn;
	mod.prcsn <= 15 ? tmp += 0.0000000000000001 : 0;
	while (mod.prcsn-- > 0)
		tmp *= 10.0;
	str[1] = num_string_base((int)tmp, 10);
	if ((len = ft_strlen(str[1])) < add_zeros)
	{
		zeros = ft_strcnew(add_zeros, '0');
		zeros = ft_strncpy(zeros + (add_zeros - len), str[1], len);
		ft_pipewrench("-s", &str[1]) && (str[1] = ft_strdup(zeros - add_zeros -\
		len)) ? ft_pipewrench("-s", &zeros - add_zeros - len) : 0;
	}
	return (str);
}

int				convert_f(t_mods modifiers, va_list ap, int i)
{
	long double		num;
	int				nbyte;
	int				neg;
	char			**str;
	char			*to_print;

	return (0);
	if (modifiers.length == 'L' || i == 19)
		num = va_arg(ap, long double);
	else
		num = va_arg(ap, double);
	neg = (num < 0.0) ? 1 : 0;
	neg == 1 ? num *= -1 : 0;
	str = num_string_modld(num, modifiers, 0);
	if (str[1][0] != '\0')
		to_print = str_3join(str[0], ".", str[1]);
	else
		to_print = ft_strdup(str[0]);
	if ((nbyte = 0) && modifiers.fl.minus == 1)
		nbyte = left_justify(modifiers, to_print, nbyte, neg);
	else
		nbyte = right_justify(modifiers, to_print, nbyte, neg);
	ft_pipewrench("--s-s", str, &to_print);
	return (nbyte);
}
