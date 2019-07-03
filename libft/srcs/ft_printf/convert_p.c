/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 21:20:04 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/26 16:35:36 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/*
**	p		The void * pointer argument is printed in hexadecimal
**			(as if by `%#x' or `%#lx').
**			The effect of padding the %p format with zeros (either by the 0 flag
**			or by specifying a precision), and the benign effect (i.e., none) of
**			the # flag on %n and %p conversions, as well as other nonsensical
**			combinations are not standard; such combinations should be avoided.
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
	if ((mod.fl.fzero && mod.width > 14) || mod.prcsn > len ||
		(mod.prcsn > 0 && num[2] == '0'))
	{
		nbyte += (int)write(1, "0x", 2);
		len -= 2;
		num += 2;
		nbyte = pad_width(mod, len, nbyte, mod.fl.fplus);
		if (mod.prcsn > len - 2)
			while ((mod.prcsn--) - len > 0)
				nbyte += (int)write(1, "0", 1);
	}
	else
	{
		nbyte = pad_width(mod, len, nbyte, mod.fl.fplus);
		if (mod.prcsn > len)
			while ((mod.prcsn--) - len > 0)
				nbyte += (int)write(1, "0", 1);
	}
	IF_RETURN(mod.prcsn == 0 && num[2] == '0',
		nbyte += (int)write(1, num, len - 1));
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

int				convert_p(t_mods modifiers, va_list ap)
{
	intptr_t	input;
	char		*tmp;
	char		*addr;
	int			nbyte;

	input = va_arg(ap, intptr_t);
	if (input)
	{
		tmp = num_string_u_base(input, 16);
		nbyte = -1;
		while (tmp[++nbyte])
			tmp[nbyte] = ft_tolower(tmp[nbyte]);
		addr = ft_strjoin("0x", tmp);
		free(tmp);
	}
	else
		addr = ft_strdup("0x0");
	if (modifiers.fl.minus == 1)
		nbyte = left_justify(modifiers, addr, 0);
	else
		nbyte = right_justify(modifiers, addr, 0);
	free(addr);
	return (nbyte);
}
