/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 21:28:19 by rpapagna          #+#    #+#             */
/*   Updated: 2019/06/20 05:18:31 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*
**	Produces a string of text stored in a buffer with variable size according
**	to a formatted string that is passed in the funciton. Parses and converts
**	variables for output to the buffer based on conversion symbols as standard
**	logic for sprintf.
*/

static int		parse_string(char *buf, char **str, va_list ap)
{
	int		i;
	t_mod	modifier;

	(*str)++;
	if (**str)
		modifier = get_mod(str, ap);
	if (!(i = get_type_specifier(**str)))
	{
		ft_strncpy(buf, *str, 1);
		(*str)++;
		(*buf)++;
		return (1);
	}
	IF_RETURN((i == 2 || i == 12) && (*str)++, i_to_buf(buf, modifier, ap));
	IF_RETURN(i == 3 && (*str)++, c_to_buf(buf, modifier, ap));
	IF_RETURN(i == 4 && (*str)++, s_to_buf(buf, modifier, ap));
	IF_RETURN((i == 8 || i == 18) && (*str)++, x_to_buf(buf, modifier, ap, i));
	return (42);
}

int				ft_sprintf(char *buf, char *str, ...)
{
	int		nbyte;
	int		i;
	va_list	ap;

	nbyte = 0;
	va_start(ap, str);
	while (*str && nbyte < PAGESIZE)
	{
		if (*str != '%')
		{
			ADD_ONE_TO_BUFF(buf, str, nbyte);
			str++;
		}
		else
		{
			i = parse_string(buf, &str, ap);
			buf += i;
			nbyte += i;
		}
	}
	IF_THEN(nbyte < PAGESIZE, *buf = '\0');
	va_end(ap);
	return (nbyte);
}

static void		ft_put_to_buf(char **buf, char *pad_char, int *nbyte)
{
	ft_strncpy(*buf, pad_char, 1);
	(*buf)++;
	(*nbyte)++;
}

int				ft_padding(char *buf, int len, t_mod mod, int nbyte)
{
	char	*pad_char;

	if ((pad_char = " ") && (len > mod.prcsn || mod.prcsn == -1))
	{
		if (mod.width > len)
		{
			IF_THEN(mod.fl.fzero && mod.prcsn == -1, pad_char = "0");
			if (!nbyte)
			{
				if (mod.fl.space && mod.fl.fzero)
					ft_put_to_buf(&buf, pad_char, &nbyte);
				while (mod.width - len - mod.neg > nbyte)
					ft_put_to_buf(&buf, pad_char, &nbyte);
			}
			else
			{
				while (mod.width - len > nbyte)
					ft_put_to_buf(&buf, pad_char, &nbyte);
			}
		}
	}
	else
		while (mod.width - mod.prcsn - mod.neg > nbyte)
			ft_put_to_buf(&buf, pad_char, &nbyte);
	return (nbyte);
}

void			left_jut(char *buf, char *num, t_mod mod, int nbyte)
{
	int		len;

	if ((len = (int)ft_strlen(num)) && mod.neg == 1)
		ft_strcpy(buf, "-");
	else if (mod.neg == 0)
	{
		if (mod.fl.fplus)
			ft_strcpy(buf, "+");
		else if (mod.fl.space)
			ft_strcpy(buf, "-");
	}
	buf++;
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
