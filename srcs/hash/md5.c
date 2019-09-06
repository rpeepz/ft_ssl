/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 22:31:22 by rpapagna          #+#    #+#             */
/*   Updated: 2019/08/28 01:57:26 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft_ssl.h"

unsigned int	g_md5_s[64] =
{
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
	5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

unsigned int	g_md5_k[64] =
{
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

static void		md5_loop(int i, t_md5 *b)
{
	if (i >= 0 && i < 16)
	{
		b->bit = (b->b & b->c) | ((~b->b) & b->d);
		b->mod = i;
	}
	else if (i >= 16 && i < 32)
	{
		b->bit = (b->d & b->b) | ((~b->d) & b->c);
		b->mod = ((5 * i) + 1) % 16;
	}
	else if (i >= 32 && i < 48)
	{
		b->bit = b->b ^ b->c ^ b->d;
		b->mod = ((3 * i) + 5) % 16;
	}
	else
	{
		b->bit = b->c ^ (b->b | (~b->d));
		b->mod = (7 * i) % 16;
	}
	b->bit = b->bit + b->a + g_md5_k[i] + *((unsigned int *)b->table[b->mod]);
	b->a = b->d;
	b->d = b->c;
	b->c = b->b;
	b->b = b->b + ((b->bit << g_md5_s[i]) | (b->bit >> (32 - g_md5_s[i])));
}

static void		md5_cycle(int count, t_md5 *b)
{
	int		i;
	int		j;

	i = -1;
	while (++i < 16)
	{
		j = -1;
		while (++j < 4)
			b->table[i][j] = b->message[(count * 64) + (i * 4) + j];
	}
	b->a = b->hash[0];
	b->b = b->hash[1];
	b->c = b->hash[2];
	b->d = b->hash[3];
	i = -1;
	while (++i < 64)
		md5_loop(i, b);
	b->hash[0] += b->a;
	b->hash[1] += b->b;
	b->hash[2] += b->c;
	b->hash[3] += b->d;
}

static void		md5_set(char *to_hash, t_md5 *b, int i, uint64_t len)
{
	len = ft_strlen(to_hash);
	b->multiples = len ? ((len + 8) / 64) + 1 : 1;
	b->message = malloc(64 * b->multiples);
	ft_bzero(b->message, (uint32_t)(64 * b->multiples));
	ft_strcpy((char *)b->message, to_hash);
	b->message[len ? len : 0] = 0x80;
	len = len << 3;
	i = -1;
	while (++i < 8)
	{
		if (!(len >> (i * 8)))
			break ;
		b->message[((64 * b->multiples) - 8) + i] = len >> (i * 8);
	}
}

static void		endian_rev(unsigned int *c)
{
	unsigned int	num;
	int				i;

	num = 0;
	i = 0;
	num += *c & 0xff;
	num = num << 8;
	while (++i < 4)
	{
		num += *c >> (i * 8) & 0xff;
		if ((i * 8) == 24)
			break ;
		num = num << 8;
	}
	*c = num;
}

char			*md5(char *buf, char *to_hash)
{
	t_md5		b;
	int			i;

	i = -1;
	ft_bzero(&b, sizeof(t_md5));
	md5_set(to_hash, &b, (int)-1, (uint64_t)0);
	b.hash[0] = 0x67452301;
	b.hash[1] = 0xefcdab89;
	b.hash[2] = 0x98badcfe;
	b.hash[3] = 0x10325476;
	while (++i < (int)b.multiples)
		md5_cycle(i, &b);
	endian_rev(&b.hash[0]);
	endian_rev(&b.hash[1]);
	endian_rev(&b.hash[2]);
	endian_rev(&b.hash[3]);
	to_hash = buf;
	ft_sprintf(to_hash, "%.8x%.8x%.8x%.8x",
		b.hash[0], b.hash[1], b.hash[2], b.hash[3]);
	free(b.message);
	return (to_hash);
}
