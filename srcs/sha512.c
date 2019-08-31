/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 03:50:33 by rpapagna          #+#    #+#             */
/*   Updated: 2019/08/12 12:12:14 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ssl.h"

static uint64_t	g_sha64bit_k[80] =
{
	0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f,
	0xe9b5dba58189dbbc, 0x3956c25bf348b538, 0x59f111f1b605d019,
	0x923f82a4af194f9b, 0xab1c5ed5da6d8118, 0xd807aa98a3030242,
	0x12835b0145706fbe, 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
	0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235,
	0xc19bf174cf692694, 0xe49b69c19ef14ad2, 0xefbe4786384f25e3,
	0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65, 0x2de92c6f592b0275,
	0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
	0x983e5152ee66dfab, 0xa831c66d2db43210, 0xb00327c898fb213f,
	0xbf597fc7beef0ee4, 0xc6e00bf33da88fc2, 0xd5a79147930aa725,
	0x06ca6351e003826f, 0x142929670a0e6e70, 0x27b70a8546d22ffc,
	0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
	0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6,
	0x92722c851482353b, 0xa2bfe8a14cf10364, 0xa81a664bbc423001,
	0xc24b8b70d0f89791, 0xc76c51a30654be30, 0xd192e819d6ef5218,
	0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8,
	0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 0x2748774cdf8eeb99,
	0x34b0bcb5e19b48a8, 0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb,
	0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3, 0x748f82ee5defb2fc,
	0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
	0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915,
	0xc67178f2e372532b, 0xca273eceea26619c, 0xd186b8c721c0c207,
	0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178, 0x06f067aa72176fba,
	0x0a637dc5a2c898a6, 0x113f9804bef90dae, 0x1b710b35131c471b,
	0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc,
	0x431d67c49c100d4c, 0x4cc5d4becb3e42b6, 0x597f299cfc657e2a,
	0x5fcb6fab3ad6faec, 0x6c44198c4a475817
};

static void		sha512_loop(t_sha64bit *s, int i, uint64_t *w)
{
	uint64_t	t1;
	uint64_t	t2;
	uint64_t	ch;
	uint64_t	maj;

	ch = (s->e & s->f) ^ ((~s->e) & s->g);
	maj = (s->a & s->b) ^ (s->a & s->c) ^ (s->b & s->c);
	t1 = s->h + E1(s->e) + ch + g_sha64bit_k[i] + w[i];
	t2 = E0(s->a) + maj;
	s->h = s->g;
	s->g = s->f;
	s->f = s->e;
	s->e = s->d + t1;
	s->d = s->c;
	s->c = s->b;
	s->b = s->a;
	s->a = t1 + t2;
}

void			sha64_cycle(int count, t_sha64bit *s, uint64_t *w, int i)
{
	while (++i < 16)
		w[i] = s->message[count][i];
	i = 15;
	while (++i < 80)
		w[i] = w[i - 16] + S0(w[i - 15]) + w[i - 7] + S1(w[i - 2]);
	s->a = s->hash[0];
	s->b = s->hash[1];
	s->c = s->hash[2];
	s->d = s->hash[3];
	s->e = s->hash[4];
	s->f = s->hash[5];
	s->g = s->hash[6];
	s->h = s->hash[7];
	i = -1;
	while (++i < 80)
		sha512_loop(s, i, w);
	s->hash[0] += s->a;
	s->hash[1] += s->b;
	s->hash[2] += s->c;
	s->hash[3] += s->d;
	s->hash[4] += s->e;
	s->hash[5] += s->f;
	s->hash[6] += s->g;
	s->hash[7] += s->h;
}

static void		sha_pad(char *to_hash, t_sha64bit *s, uint64_t len)
{
	int			i;
	int			u;
	uint64_t	n;

	n = 0;
	i = 0;
	u = 56;
	while (n < len)
	{
		u = (n % 8 ? u - 8 : 56);
		s->message[i][(n % 128) / 8] |=
		(((uint64_t)to_hash[n] << u) & (0xffffffffffffffff >> (((n) % 8)) * 8));
		((++n) % 128) ? 0 : i++;
	}
	u = (n % 8) ? u - 8 : 56;
	s->message[i][(n) % 128 / 8] |= (uint64_t)0x80 << u;
	s->message[s->multiples - 1][14] = ((uint64_t)len * 8) >> 56;
	s->message[s->multiples - 1][15] = ((uint64_t)len * 8) & 0xffffffffffffffff;
}

void			sha64_start(char *to_hash, t_sha64bit *s)
{
	int			i;
	uint64_t	len;
	char		*cpy;

	cpy = ft_strdup(to_hash);
	i = -1;
	len = (ft_strlen(to_hash) * 8) + 1;
	while (len % 1024 != 896)
		len++;
	s->multiples = (len += 128) / 1024;
	s->message = (uint64_t**)malloc(sizeof(uint64_t*) * s->multiples);
	while (++i < s->multiples)
	{
		s->message[i] = (uint64_t*)malloc(sizeof(uint64_t) * 16);
		ft_bzero(s->message[i], sizeof(uint64_t) * 16);
	}
	sha_pad(cpy, s, LEN(cpy));
	free(cpy);
}

char			*sha512(char *buf, char *to_hash)
{
	t_sha64bit	s;
	uint64_t	w[80];
	int			i;

	i = -1;
	ft_bzero(&s, sizeof(t_sha64bit));
	sha64_start(to_hash, &s);
	s.hash[0] = 0x6a09e667f3bcc908;
	s.hash[1] = 0xbb67ae8584caa73b;
	s.hash[2] = 0x3c6ef372fe94f82b;
	s.hash[3] = 0xa54ff53a5f1d36f1;
	s.hash[4] = 0x510e527fade682d1;
	s.hash[5] = 0x9b05688c2b3e6c1f;
	s.hash[6] = 0x1f83d9abfb41bd6b;
	s.hash[7] = 0x5be0cd19137e2179;
	while (++i < (s.multiples))
		sha64_cycle(i, &s, w, -1);
	to_hash = buf;
	ft_sprintf(to_hash,
		"%.16llx%.16llx%.16llx%.16llx%.16llx%.16llx%.16llx%.16llx",
		s.hash[0], s.hash[1], s.hash[2], s.hash[3],
		s.hash[4], s.hash[5], s.hash[6], s.hash[7]);
	free_message(s.multiples, s.message);
	free(s.message);
	return (to_hash);
}
