/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 03:50:26 by rpapagna          #+#    #+#             */
/*   Updated: 2019/08/12 12:12:05 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ssl.h"

unsigned int	g_sha256_k[64] =
{
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
	0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
	0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
	0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
	0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
	0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

static void		sha256_loop(int i, t_sha *s)
{
	unsigned int	s0;
	unsigned int	s1;
	unsigned int	temp1;
	unsigned int	ch;
	unsigned int	maj;

	s1 = ((s->e >> 6) | (s->e << (32 - 6))) ^
		((s->e >> 11) | (s->e << (32 - 11))) ^
		((s->e >> 25) | (s->e << (32 - 25)));
	ch = (s->e & s->f) ^ ((~s->e) & s->g);
	temp1 = s->h + s1 + ch + g_sha256_k[i] + s->array[i];
	s0 = ((s->a >> 2) | (s->a << (32 - 2))) ^
		((s->a >> 13) | (s->a << (32 - 13))) ^
		((s->a >> 22) | (s->a << (32 - 22)));
	maj = (s->a & s->b) ^ (s->a & s->c) ^ (s->b & s->c);
	s->h = s->g;
	s->g = s->f;
	s->f = s->e;
	s->e = s->d + temp1;
	s->d = s->c;
	s->c = s->b;
	s->b = s->a;
	s->a = temp1 + s0 + maj;
}

static void		sha256_shift(int count, t_sha *s)
{
	int				i;
	int				j;
	unsigned int	sp1;
	unsigned int	sp2;

	i = -1;
	while (++i < 16)
	{
		j = -1;
		s->array[i] = 0;
		while (++j < 4)
			s->array[i] += s->message[count * 64 + i * 4 + j] << (8 * (3 - j));
	}
	i = 15;
	while (++i < 64)
	{
		sp1 = ((s->array[i - 15] >> 7) | (s->array[i - 15] << (32 - 7))) ^
			((s->array[i - 15] >> 18) | (s->array[i - 15] << (32 - 18))) ^
			(s->array[i - 15] >> 3);
		sp2 = ((s->array[i - 2] >> 17) | (s->array[i - 2] << (32 - 17))) ^
			((s->array[i - 2] >> 19) | (s->array[i - 2] << (32 - 19))) ^
			(s->array[i - 2] >> 10);
		s->array[i] = s->array[i - 16] + sp1 + s->array[i - 7] + sp2;
	}
}

static void		sha_cycle(int count, t_sha *s)
{
	int				i;

	i = -1;
	sha256_shift(count, s);
	s->a = s->hash[0];
	s->b = s->hash[1];
	s->c = s->hash[2];
	s->d = s->hash[3];
	s->e = s->hash[4];
	s->f = s->hash[5];
	s->g = s->hash[6];
	s->h = s->hash[7];
	while (++i < 64)
		sha256_loop(i, s);
	s->hash[0] += s->a;
	s->hash[1] += s->b;
	s->hash[2] += s->c;
	s->hash[3] += s->d;
	s->hash[4] += s->e;
	s->hash[5] += s->f;
	s->hash[6] += s->g;
	s->hash[7] += s->h;
}

static void		sha_set(char *to_hash, t_sha *s, int i, uint64_t len)
{
	s->hash[0] = 0x6a09e667;
	s->hash[1] = 0xbb67ae85;
	s->hash[2] = 0x3c6ef372;
	s->hash[3] = 0xa54ff53a;
	s->hash[4] = 0x510e527f;
	s->hash[5] = 0x9b05688c;
	s->hash[6] = 0x1f83d9ab;
	s->hash[7] = 0x5be0cd19;
	len = ft_strlen(to_hash);
	s->multiples = len ? ((len + 8) / 64) + 1 : 1;
	s->message = malloc(64 * s->multiples);
	ft_bzero(s->message, (int)(64 * s->multiples));
	ft_strcpy((char *)s->message, to_hash);
	s->message[len ? len : 0] = 1 << 7;
	len = len << 3;
	while (++i < 8)
		s->message[64 * s->multiples - i - 1] = len >> (i * 8);
}

char			*sha256(char *buf, char *to_hash)
{
	t_sha		s;
	int			i;

	i = -1;
	ft_bzero(&s, sizeof(t_sha));
	sha_set(to_hash, &s, (int)-1, (uint64_t)0);
	while (++i < (int)(s.multiples))
		sha_cycle(i, &s);
	to_hash = buf;
	ft_sprintf(to_hash, "%.8x%.8x%.8x%.8x%.8x%.8x%.8x%.8x",
		s.hash[0], s.hash[1], s.hash[2], s.hash[3],
		s.hash[4], s.hash[5], s.hash[6], s.hash[7]);
	free(s.message);
	return (to_hash);
}
