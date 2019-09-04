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

static uint32_t	g_sha32bit_k[64] =
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

static void		sha256_loop(int i, t_sha32bit *s, uint32_t *w)
{
	uint32_t	t1;
	uint32_t	t2;
	uint32_t	ch;
	uint32_t	maj;

	ch = (s->e & s->f) ^ ((~s->e) & s->g);
	maj = (s->a & s->b) ^ (s->a & s->c) ^ (s->b & s->c);
	t1 = s->h + E1_32(s->e) + ch + g_sha32bit_k[i] + w[i];
	t2 = E0_32(s->a) + maj;
	s->h = s->g;
	s->g = s->f;
	s->f = s->e;
	s->e = s->d + t1;
	s->d = s->c;
	s->c = s->b;
	s->b = s->a;
	s->a = t1 + t2;
}

void			sha32_cycle(int count, t_sha32bit *s, uint32_t *w, int i)
{
	while (++i < 16)
		w[i] = s->message[count][i];
	i = 15;
	while (++i < 64)
		w[i] = w[i - 16] + S0_32(w[i - 15]) + w[i - 7] + S1_32(w[i - 2]);
	s->a = s->hash[0];
	s->b = s->hash[1];
	s->c = s->hash[2];
	s->d = s->hash[3];
	s->e = s->hash[4];
	s->f = s->hash[5];
	s->g = s->hash[6];
	s->h = s->hash[7];
	i = -1;
	while (++i < 64)
		sha256_loop(i, s, w);
	s->hash[0] += s->a;
	s->hash[1] += s->b;
	s->hash[2] += s->c;
	s->hash[3] += s->d;
	s->hash[4] += s->e;
	s->hash[5] += s->f;
	s->hash[6] += s->g;
	s->hash[7] += s->h;
}

static void		sha_pad(char *to_hash, t_sha32bit *s, uint64_t len)
{
	int			i;
	uint64_t	n;

	n = 0;
	i = 0;
	while (n < len)
	{
		s->message[i][n % 64 / 4] |=
		((to_hash[n] << (3 - ((n) % 4)) * 8) & (0xffffffff >> (((n) % 4)) * 8));
		(((++n) % 64)) == 0 ? i++ : 0;
	}
	s->message[i][(n) % 64 / 4] |= 0x80 << (3 - ((n) % 4)) * 8;
	s->message[s->multiples - 1][14] = (uint32_t)((len * 8) >> 32);
	s->message[s->multiples - 1][15] = (uint32_t)((len * 8) & 0xffffffff);
}

void			sha32_set(char *to_hash, t_sha32bit *s)
{
	int			i;
	uint64_t	len;

	i = -1;
	len = (ft_strlen(to_hash) * 8) + 1;
	while (len % 512 != 448)
		len++;
	s->multiples = (len += 64) / 512;
	s->message = (uint32_t**)malloc(sizeof(uint32_t*) * s->multiples);
	while (++i < s->multiples)
	{
		s->message[i] = (uint32_t*)malloc(sizeof(uint32_t) * 16);
		ft_bzero(s->message[i], sizeof(uint32_t) * 16);
	}
	sha_pad(to_hash, s, LEN(to_hash));
}

char			*sha256(char *buf, char *to_hash)
{
	t_sha32bit	s;
	uint32_t	w[64];
	int			i;

	i = -1;
	ft_bzero(&s, sizeof(t_sha32bit));
	sha32_set(to_hash, &s);
	s.hash[0] = 0x6a09e667;
	s.hash[1] = 0xbb67ae85;
	s.hash[2] = 0x3c6ef372;
	s.hash[3] = 0xa54ff53a;
	s.hash[4] = 0x510e527f;
	s.hash[5] = 0x9b05688c;
	s.hash[6] = 0x1f83d9ab;
	s.hash[7] = 0x5be0cd19;
	while (++i < s.multiples)
		sha32_cycle(i, &s, w, -1);
	to_hash = buf;
	ft_sprintf(to_hash, "%.8x%.8x%.8x%.8x%.8x%.8x%.8x%.8x",
		s.hash[0], s.hash[1], s.hash[2], s.hash[3],
		s.hash[4], s.hash[5], s.hash[6], s.hash[7]);
	free_message(s.multiples, (uint64_t **)s.message);
	free(s.message);
	return (to_hash);
}
