/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 03:50:21 by rpapagna          #+#    #+#             */
/*   Updated: 2019/08/18 20:40:47 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ssl.h"

unsigned int    left_rotate(unsigned int x, unsigned int c)
{
    return ((x << c) | (x >> (32 - c)));
}
void            byte_rev(unsigned int *c)
{
    unsigned int    num;
    int             i;

    num = 0;
    i = 0;
    num += *c & 0xff;
    num = LEFT_SHIFT;
    while (++i < 4)
    {
        num += *c >> (i * 8) & 0xff;
        if ((i * 8) == 24)
            break;
        num = LEFT_SHIFT;
    }
    *c = num;
}

unsigned int	g_md5_s[64] =
{
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
	5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

unsigned int	g_md5_K[64] =
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

static void 	md5_loop(int i, t_md5 *md)
{
	if (0 <= i && i <= 15)
	{
		md->f = (md->b & md->c) | ((~md->b) & md->d);
		md->g = i;
	}
	else if (16 <= i && i <= 31)
	{
		md->f = (md->d & md->b) | ((~md->d) & md->c);
		md->g = (5 * i + 1) % 16;
	}
	else if (32 <= i && i <= 47)
	{
		md->f = md->b ^ md->c ^ md->d;
		md->g = (3 * i + 5) % 16;
	}
	else
	{
	md->f = md->c ^ (md->b | (~md->d));
		md->g = (7 * i) % 16;
	}
	md->f = md->f + md->a + g_md5_K[i] + *((unsigned int *)(md->mem[md->g]));
	md->a = md->d;
	md->d = md->c;
	md->c = md->b;
	md->b = md->b + left_rotate(md->f, g_md5_s[i]);
}

static void 	md5_oper(int i, t_md5 *md)
{
	int		index;
	int		j;

	index = -1;
	while (++index < 16)
	{
		j = -1;
		while (++j < 4)
			md->mem[index][j] = md->msg[i * 64 + index * 4 + j];
	}
	md->a = md->a_1;
	md->b = md->b_1;
	md->c = md->c_1;
	md->d = md->d_1;
	index = -1;
	while (++index < 64)
		md5_loop(index, md);
	md->a_1 += md->a;
	md->b_1 += md->b;
	md->c_1 += md->c;
	md->d_1 += md->d;
}

static void 	md5_set(char *to_hash, t_md5 *md)
{
	int i;
	uint64_t	len;

	md->a_1 = 0x67452301;
	md->b_1 = 0xefcdab89;
	md->c_1 = 0x98badcfe;
	md->d_1 = 0x10325476;
	len = 0;
	if (to_hash)
		md->set = (ft_strlen(to_hash) + 8) / 64 + 1;
	else
		md->set = 1;
	md->msg = (unsigned char *)malloc(64 * md->set);
	i = -1;
	while (++i < (int)(64 * md->set))
		md->msg[i] = 0;
	i = -1;
	while (to_hash && to_hash[++i])
		md->msg[i] = to_hash[i];
	md->msg[i == -1 ? 0 : i] = 1 << 7;
	len = i << 3;
	i = -1;
	while (++i < 8)
		md->msg[64 * md->set - 8 + i] = len >> (i * 8);
}

char			*md5(char *buf, char *to_hash)
{
	t_md5	md;
	int		i;

	i = -1;
	ft_bzero(&md, 10);
	md5_set(to_hash, &md);
	while (++i < (int)(md.set))
		md5_oper(i, &md);
	byte_rev(&md.a_1);
	byte_rev(&md.b_1);
	byte_rev(&md.c_1);
	byte_rev(&md.d_1);
	to_hash = buf;
	ft_sprintf(to_hash, "%.8x%.8x%.8x%.8x", md.a_1, md.b_1, md.c_1, md.d_1);
	free(md.msg);
	return (to_hash);
}
