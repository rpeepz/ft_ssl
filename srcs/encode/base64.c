/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 01:56:02 by rpapagna          #+#    #+#             */
/*   Updated: 2019/11/17 21:11:10 by rpapagna         ###   ########.fr       */
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

unsigned char	g_base64_decode[123] =
{
	' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
	' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
	' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 62, ' ',
	' ', ' ', 63, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, ' ', ' ',
	' ', ' ', ' ', ' ', ' ', 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
	10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
	25, ' ', ' ', ' ', ' ', ' ', ' ', 26, 27, 28, 29, 30, 31, 32, 33,
	34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48,
	49, 50, 51
};

/*
**	No padding on ASN1
**	ft_putchar_fd(g_base64[edata[2]], fd);
**	ft_putchar_fd(g_base64[edata[3]], fd);
*/

void			base64_nstr_fd(uint8_t *in, int len, int fd)
{
	int			i;
	uint8_t		edata[4];

	i = 0;
	while (i < len)
	{
		DEBUG ? ft_printf("%02x %02x %02x\n", in[i], in[i + 1], in[i + 2]) : 0;
		ft_bzero(edata, 4);
		edata[0] |= in[i] >> 2;
		edata[1] |= ((in[i] & 0x03) << 4);
		edata[1] |= (in[i + 1] >> 4);
		edata[2] |= ((in[i + 1] & 0x0F) << 2);
		edata[2] |= (in[i + 2] >> 6);
		edata[3] |= (in[i + 2] & 0x3F);
		ft_putchar_fd(g_base64[edata[0]], fd);
		ft_putchar_fd(g_base64[edata[1]], fd);
		ft_putchar_fd((!edata[2] && len - i < 2) ?
		'=' : g_base64[edata[2]], fd);
		ft_putchar_fd((!edata[3] && len - i < 3) ?
		'=' : g_base64[edata[3]], fd);
		i += 3;
		(i % 48) == 0 ? ft_putchar_fd('\n', fd) : 0;
	}
	(i % 48) ? ft_putchar_fd('\n', fd) : 0;
}

int				base64_decode(uint8_t *enc, uint8_t *dec, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		if ((i + 4) % 64 == 0)
			i++;
		dec[3 * (i / 4)] |= (g_base64_decode[enc[i]]) << 2;
		dec[3 * (i / 4)] |= ((g_base64_decode[enc[i + 1]] & 0x30) >> 4);
		dec[3 * (i / 4) + 1] |= ((g_base64_decode[enc[i + 1]] & 0x0F) << 4);
		dec[3 * (i / 4) + 1] |= (g_base64_decode[enc[i + 2]] >> 2);
		dec[3 * (i / 4) + 2] |= (g_base64_decode[enc[i + 2]] << 6);
		dec[3 * (i / 4) + 2] |= g_base64_decode[enc[i + 3]];
		i += 4;
	}
	return (i);
}