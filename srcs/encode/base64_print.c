/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 01:56:02 by rpapagna          #+#    #+#             */
/*   Updated: 2019/11/12 18:21:03 by rpapagna         ###   ########.fr       */
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
	buf[0] = (edata & 0xFC0000) >> 18;
	buf[1] = (edata & 0x3F000) >> 12;
	buf[2] = (edata & 0xFC0) >> 6;
	buf[3] = (edata & 0x3F);
	i = 0;
	while (i < 4)
	{
		near_end < 3 && !buf[i] ?
		ft_putchar_fd('=', fd) : ft_putchar_fd(g_base64[buf[i]], fd);
		// if (!buf[i] && near_end < 3)
		// 	ft_putchar_fd('=', fd);
		// else if (buf[i] < 26)
		// 	ft_putchar_fd(buf[i] + 'A', fd);
		// else if (buf[i] < 52)
		// 	ft_putchar_fd(buf[i] + 'G', fd);
		// else if (buf[i] < 62)
		// 	ft_putchar_fd(buf[i] - 4, fd);
		// else
		// {
		// 	ft_putstr("YEEHAW\n");
		// 	ft_putchar_fd(buf[i] % 2 ? '/' : '+', fd);
		// }
		i++;
	}
}

void			base64_str_fd(char *in, int fd)
{
	char	buf[PAGESIZE];
	int		i;
	int		len;
	int		edata;

	i = 0;
	ft_bzero(buf, PAGESIZE);
	len = ft_strlen(in) + 3;
	ft_printf("[%02x%02x%02x%02x%02x%s]\n", SEQUENCE, len, INT, V, V1, in);
	ft_sprintf(buf,
	"%02x%02x%02x%02x%02x%s",
	SEQUENCE, len, INT, V, V1, in);
	// ft_printf("[%s]\n", in);
	ft_printf("[%02x]\n", len);
	while(i < len)
	{
		edata = 0;
		edata += in[i];
		edata <<= 8;
		edata += in[(i + 1) < len ? i + 1 : len];
		edata <<= 8;
		edata += in[(i + 2) < len ? i + 2 : len];
		print_base64_fd(edata, len - i, fd);
		i += 3;
		if (!(i <= len) && !(i % 48))
			ft_putchar('\n');
	}
}
