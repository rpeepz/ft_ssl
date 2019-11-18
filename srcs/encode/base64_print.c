/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_print.c                                     :+:      :+:    :+:   */
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
