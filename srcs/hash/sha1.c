/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 03:50:26 by rpapagna          #+#    #+#             */
/*   Updated: 2019/10/12 18:36:03 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"

static __uint32_t	g_k[4] =
{
	0x5A827999, 0x6ED9EBA1, 0x8F1BBCDC, 0xCA62C1D6
};

static void		sha1_loop(int i, t_sha32bit *s, __uint32_t *w)
{
	__uint32_t		tmp;

	if (i >= 0 && i < 20)
		s->f = (s->b & s->c) | ((~s->b) & s->d);
	else if (i >= 20 && i < 40)
		s->f = s->b ^ s->c ^ s->d;
	else if (i >= 40 && i < 60)
		s->f = (s->b & s->c) | (s->b & s->d) | (s->c & s->d);
	else
		s->f = s->b ^ s->c ^ s->d;
	tmp = ((s->a << 5) | (s->a >> (32 - 5))) + s->f + s->e + g_k[i / 20] + w[i];
	s->e = s->d;
	s->d = s->c;
	s->c = ((s->b << 30) | (s->b >> (32 - 30)));
	s->b = s->a;
	s->a = tmp;
}

void			sha1_cycle(int count, t_sha32bit *s, __uint32_t *w, int i)
{
	__uint32_t		pos;

	while (++i < 16)
		w[i] = s->message[count][i];
	i = 15;
	while (++i < 80)
	{
		pos = w[i - 3] ^ (w[i - 8]) ^ w[i - 14] ^ (w[i - 16]);
		w[i] = (pos << 1) | (pos >> (32 - 1));
	}
	s->a = s->hash[0];
	s->b = s->hash[1];
	s->c = s->hash[2];
	s->d = s->hash[3];
	s->e = s->hash[4];
	i = -1;
	while (++i < 80)
		sha1_loop(i, s, w);
	s->hash[0] += s->a;
	s->hash[1] += s->b;
	s->hash[2] += s->c;
	s->hash[3] += s->d;
	s->hash[4] += s->e;
}

char			*sha1(char *buf, char *to_hash)
{
	t_sha32bit	s;
	__uint32_t	w[80];
	int			i;

	i = -1;
	ft_bzero(&s, sizeof(t_sha32bit));
	sha32_set(to_hash, &s);
	s.hash[0] = 0x67452301;
	s.hash[1] = 0xEFCDAB89;
	s.hash[2] = 0x98BADCFE;
	s.hash[3] = 0x10325476;
	s.hash[4] = 0xC3D2E1F0;
	while (++i < s.multiples)
		sha1_cycle(i, &s, w, -1);
	to_hash = buf;
	ft_sprintf(to_hash, "%.8x%.8x%.8x%.8x%.8x",
		s.hash[0], s.hash[1], s.hash[2], s.hash[3], s.hash[4]);
	free_message(s.multiples, (__uint64_t **)s.message);
	free(s.message);
	return (to_hash);
}
