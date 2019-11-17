/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asn1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 17:48:28 by rpapagna          #+#    #+#             */
/*   Updated: 2019/11/16 17:52:13 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"
#include "encode.h"

static char		byte_len(__uint64_t n)
{
	char	len;

	len = 0;
	while (n)
	{
		len++;
		n >>= 8;
	}
	return (len);
}

static uint8_t  *byte_string(uint8_t *buf, __uint64_t n)
{
	int		i;
	int		p;
	int		trig;

	i = 0;
	p = 0;
	trig = 0;
	ft_bzero(buf, 10);
	while (i < 8)
	{
		if (trig || (n & (0xFF << 8 * (7 - i))) >> 8 * (7 - i))
		{
			buf[p] = ((n & (0xFF << 8 * (7 - i))) >> 8 * (7 - i));
			if (!trig && (buf[p] & 0x80))
			{
				buf[p + 1] = buf[p];
				buf[p++] = 0xFF;
			}
			if (!buf[p])
				buf[p] = 0xFF;
			p++;
			trig = 1;
		}
		i++;
	}
	return (buf);
}

static void		dump_to_buf(uint8_t *buf, char c, uint8_t *s, int *len)
{
	int		i;
	int		n;

	if (!s)
	{
		buf[*len] = c;
		++(*len);
	}
	else
	{
		i = 0;
		n = LEN((char*)s);
		while (i < n || s[n])
		{
			buf[*len] = s[i];
			++(*len);
			++i;
		}
	}
}

static void		asn1_cont(t_rsa gg, uint8_t *buf, uint8_t *buf2, int *len)
{
	uint8_t		copy[PAGESIZE];
	int			index;

	dump_to_buf(buf, byte_string(buf2, gg.dmp1)[0] == 0xFF ?
	byte_len(gg.dmp1) + 1 : byte_len(gg.dmp1), NULL, len);
	dump_to_buf(buf, 0, byte_string(buf2, gg.dmp1), len);
	dump_to_buf(buf, INT, NULL, len);
	dump_to_buf(buf, byte_string(buf2, gg.dmq1)[0] == 0xFF ?
	byte_len(gg.dmq1) + 1 : byte_len(gg.dmq1), NULL, len);
	dump_to_buf(buf, 0, byte_string(buf2, gg.dmq1), len);
	dump_to_buf(buf, INT, NULL, len);
	dump_to_buf(buf, byte_string(buf2, gg.iqmp)[0] == 0xFF ?
	byte_len(gg.iqmp) + 1 : byte_len(gg.iqmp), NULL, len);
	dump_to_buf(buf, 0, byte_string(buf2, gg.iqmp), len);
	ft_memcpy(copy, buf, *len);
	ft_bzero(buf, PAGESIZE);
	*len += 3;
	index = 0;
	dump_to_buf(buf, SEQUENCE, NULL, &index);
	dump_to_buf(buf, (char)*len, NULL, &index);
	dump_to_buf(buf, INT, NULL, &index);
	dump_to_buf(buf, V, NULL, &index);
	dump_to_buf(buf, V1, NULL, &index);
	dump_to_buf(buf, 0, copy, &index);
	*len += 2;
}

void			asn1(t_rsa gg, uint8_t *buf, uint8_t *buf2, int *len)
{
	dump_to_buf(buf, INT, NULL, len);
	dump_to_buf(buf, byte_string(buf2, gg.n)[0] == 0xFF ?
	byte_len(gg.n) + 1 : byte_len(gg.n), NULL, len);
	dump_to_buf(buf, 0, byte_string(buf2, gg.n), len);
	dump_to_buf(buf, INT, NULL, len);
	dump_to_buf(buf, byte_len(gg.e), NULL, len);
	dump_to_buf(buf, 0, byte_string(buf2, gg.e), len);
	dump_to_buf(buf, INT, NULL, len);
	dump_to_buf(buf, byte_string(buf2, gg.d)[0] == 0xFF ?
	byte_len(gg.d) + 1 : byte_len(gg.d), NULL, len);
	dump_to_buf(buf, 0, byte_string(buf2, gg.d), len);
	dump_to_buf(buf, INT, NULL, len);
	dump_to_buf(buf, byte_string(buf2, gg.p)[0] == 0xFF ?
	byte_len(gg.p) + 1 : byte_len(gg.p), NULL, len);
	dump_to_buf(buf, 0, byte_string(buf2, gg.p), len);
	dump_to_buf(buf, INT, NULL, len);
	dump_to_buf(buf, byte_string(buf2, gg.q)[0] == 0xFF ?
	byte_len(gg.q) + 1 : byte_len(gg.q), NULL, len);
	dump_to_buf(buf, 0, byte_string(buf2, gg.q), len);
	dump_to_buf(buf, INT, NULL, len);
	asn1_cont(gg, buf, buf2, len);
}
