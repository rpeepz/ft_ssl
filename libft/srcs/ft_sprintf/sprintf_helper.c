/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprintf_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 21:28:19 by rpapagna          #+#    #+#             */
/*   Updated: 2019/11/01 22:33:03 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sprintf.h"

void			add_one_to_buf(char *buf, int c, int *n)
{
	ft_strncpy(buf, (const char *)&c, 1);
	buf++;
	++(*n);
}

void			add_to_buf(char *buf, char *src, int *n, int len)
{
	ft_strncpy(buf, src, len);
	buf += len;
	(*n) += len;
}

int				ft_padding(char *buf, int len, t_mod mod, int nbyte)
{
	char	*pad_char;

	if ((pad_char = " ") && (len > mod.prcsn || mod.prcsn == -1))
	{
		if (mod.width > len)
		{
			mod.fl.fzero && mod.prcsn == -1 ? pad_char = "0" : 0;
			if (!nbyte)
			{
				if (mod.fl.space && mod.fl.fzero)
					add_one_to_buf(buf, *pad_char, &nbyte);
				while (mod.width - len - mod.neg > nbyte)
					add_one_to_buf(buf, *pad_char, &nbyte);
			}
			else
			{
				while (mod.width - len > nbyte)
					add_one_to_buf(buf, *pad_char, &nbyte);
			}
		}
	}
	else
		while (mod.width - mod.prcsn - mod.neg > nbyte)
			add_one_to_buf(buf, *pad_char, &nbyte);
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
	add_to_buf(buf, num, &nbyte, len);
	while (nbyte < mod.width)
	{
		add_one_to_buf(buf, ' ', &nbyte);
	}
}
