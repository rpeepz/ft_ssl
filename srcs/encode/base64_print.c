/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 01:56:02 by rpapagna          #+#    #+#             */
/*   Updated: 2019/11/16 18:03:32 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encode.h"

unsigned char	g_base64[64] =
{
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
	'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd',
	'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
	't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7',
	'8', '9', '+', '/'
};

void			print_base64_fd(int edata, int near_end, int fd)
{
	unsigned char	buf[4];
	int				i;

	ft_bzero(buf, 4);
	buf[0] = (edata & 0xFF000000) >> 24;
	buf[1] = (edata & 0xFF0000) >> 16;
	buf[2] = (edata & 0xFF00) >> 8;
	buf[3] = (edata & 0xFF);
	i = 0;
	while (i < 4)
	{
		near_end < 3 && !buf[i] ?
		ft_putchar_fd('=', fd) : ft_putchar_fd(g_base64[buf[i]], fd);
		i++;
	}
	if (DEBUG)
		ft_printf("--- %02d %02d %02d %02d\n", buf[0], buf[1], buf[2], buf[3]);
}

void			base64_nstr_fd(char *in, int len, int fd)
{
	int		i;
	int		edata;

	i = 0;
	while(i < len)
	{
		edata = 0;
		edata += (in[i] & 0xFC) >> 2;
		edata <<= 8;
		edata += (in[i] & 0x03) << 4;
		edata += (in[(i + 1) < len ? i + 1 : len] & 0xF0) >> 4;
		edata <<= 8;
		edata += (in[(i + 1) < len ? i + 1 : len] & 0x0F) << 2;
		edata += (in[(i + 2) < len ? i + 2 : len] & 0xC0) >> 6;
		edata <<= 8;
		edata += in[(i + 2) < len ? i + 2 : len] & 0x3F;
		print_base64_fd(edata, (len) - i, fd);
		i += 3;
		if (!(i <= (len)) && !(i % 48))
			ft_putchar('\n');
	}
	if ((i <= (len)) || (i % 48))
		ft_putchar('\n');
}
