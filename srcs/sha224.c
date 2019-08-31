/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha244.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 03:50:26 by rpapagna          #+#    #+#             */
/*   Updated: 2019/08/12 12:12:05 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ssl.h"

char			*sha224(char *buf, char *to_hash)
{
	t_sha32bit	s;
	uint32_t	w[64];
	int			i;

	i = -1;
	ft_bzero(&s, sizeof(t_sha32bit));
	sha32_set(to_hash, &s);
	s.hash[0] = 0xc1059ed8;
	s.hash[1] = 0x367cd507;
	s.hash[2] = 0x3070dd17;
	s.hash[3] = 0xf70e5939;
	s.hash[4] = 0xffc00b31;
	s.hash[5] = 0x68581511;
	s.hash[6] = 0x64f98fa7;
	s.hash[7] = 0xbefa4fa4;
	while (++i < (int)(s.multiples))
		sha32_cycle(i, &s, w, -1);
	to_hash = buf;
	ft_sprintf(to_hash, "%.8x%.8x%.8x%.8x%.8x%.8x%.8x",
		s.hash[0], s.hash[1], s.hash[2], s.hash[3],
		s.hash[4], s.hash[5], s.hash[6]);
	free_message(s.multiples, (uint64_t **)s.message);
	free(s.message);
	return (to_hash);
}
