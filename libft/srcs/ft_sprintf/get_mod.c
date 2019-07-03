/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 23:49:35 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/26 16:33:54 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static t_fl		get_flags(char **str)
{
	t_fl	flag;

	flag.space = 0;
	flag.pound = 0;
	flag.fplus = 0;
	flag.minus = 0;
	flag.fzero = 0;
	while (is_flag(**str))
	{
		if (**str == ' ')
			flag.space = 1;
		else if (**str == '#')
			flag.pound = 1;
		else if (**str == '+')
			flag.fplus = 1;
		else if (**str == '-')
			flag.minus = 1;
		else if (**str == '0')
			flag.fzero = 1;
		(*str)++;
	}
	return (flag);
}

static int		get_width(char **str, va_list ap)
{
	int		width;

	width = 0;
	if (**str == '*')
	{
		width = va_arg(ap, int);
		(*str)++;
	}
	if (ft_isdigit(**str))
	{
		width = ft_atoi(*str);
		while (ft_isdigit(**str))
			(*str)++;
	}
	if (**str == '*')
	{
		width = va_arg(ap, int);
		(*str)++;
	}
	return (width);
}

static int		get_precision(char **str, va_list ap)
{
	int		precision;

	precision = -1;
	if (**str == '.')
	{
		precision = 0;
		(*str)++;
		if (ft_isdigit(**str))
		{
			precision = ft_atoi(*str);
			IF_THEN(precision < 0, precision = -1);
			while (ft_isdigit(**str))
				(*str)++;
		}
		else if (**str == '*')
		{
			precision = va_arg(ap, int);
			IF_THEN(precision < 0, precision = -1);
			(*str)++;
		}
	}
	if (precision >= 0)
		return (precision);
	return (-1);
}

static int		get_length(char **str)
{
	int		length;

	length = 0;
	if (**str == 'L')
		length = (int)'L';
	else if (**str == 'h' && *(*str + 1) != 'h')
		length = (int)'h';
	else if (**str == 'h' && *(*str + 1) == 'h')
		length = (int)('h' + 'h');
	else if (**str == 'l' && *(*str + 1) != 'l')
		length = (int)'l';
	else if (**str == 'l' && *(*str + 1) == 'l')
		length = (int)('l' + 'l');
	else if (get_undef_length(**str))
		length = (int)('z');
	if (length > 0)
	{
		if (length >= 'h' + 'h')
			(*str) += 2;
		else
			(*str) += 1;
	}
	while (length && get_undef_length(**str))
		(*str) += 1;
	return (length);
}

t_mod			get_mod(char **str, va_list ap)
{
	t_mod modifiers;

	modifiers.fl = get_flags(str);
	modifiers.width = get_width(str, ap);
	if (modifiers.width < 0)
	{
		modifiers.width *= -1;
		modifiers.fl.minus = 1;
	}
	modifiers.prcsn = get_precision(str, ap);
	modifiers.length = get_length(str);
	return (modifiers);
}
/*
**	the format for my getter functions were
**	inspired by the great work of my friend, Chris Bagdon
**	https://github.com/cbg119/42-ft_printf/blob/master/src/options.c
**
**	first function call in get_mods may be replaced with below
**	to add bitwise operation in order to improve speed
**	modifiers.flag_bits = get_flags(str);
**
**	static void		set_bit(char **str, char bit)
**	{
**		do bit stuff
**	}
**
**	static char		get_flags(char **str)
**	{
**		char	bit;
**
**		bit = 0;
**		while (is_flag(**str))
**		{
**			set_bit(**str, &bit);
**			(*str)++;
**		}
**		return (bit);
**	}
*/
