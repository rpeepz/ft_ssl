/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 01:56:02 by rpapagna          #+#    #+#             */
/*   Updated: 2019/11/05 02:03:18 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encode.h"

void			print_base64_fd(int edata, int fd)
{
	char	buf[4];
	int		i;

	ft_bzero(buf, 4);
	buf[0] = (edata & 0xFC0000) >> 18;
	buf[1] = (edata & 0x3F000) >> 12;
	buf[2] = (edata & 0xFC0) >> 6;
	buf[3] = (edata & 0x3F);
	i = 0;
	while (i < 4)
	{
		if (!buf[i])
			ft_putchar_fd('=', fd);
		else if (buf[i] < 26)
			ft_putchar_fd(buf[i] + 'A', fd);
		else if (buf[i] < 52)
			ft_putchar_fd(buf[i] + 'G', fd);
		else if (buf[i] < 62)
			ft_putchar_fd(buf[i] - 4, fd);
		else
			ft_putchar_fd(buf[i] % 2 ? '/' : '+', fd);
		i++;
	}
}

void			base64_str_fd(char *in, int fd)
{
	int		i;
	int		len;
	int		edata;

	i = 0;
	len = ft_strlen(in);
	while(i < len)
	{
		edata = 0;
		edata += in[i];
		edata <<= 8;
		edata += in[(i + 1) < len ? i + 1 : len];
		edata <<= 8;
		edata += in[(i + 2) < len ? i + 2 : len];
		print_base64_fd(edata, fd);
		i += 3;
	}
}
