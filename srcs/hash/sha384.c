/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha384.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 03:50:33 by rpapagna          #+#    #+#             */
/*   Updated: 2019/10/12 18:36:41 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"

char			*sha384(char *buf, char *to_hash)
{
	t_sha64bit	s;
	__uint64_t	w[80];
	int			i;

	i = -1;
	ft_bzero(&s, sizeof(t_sha64bit));
	sha64_start(to_hash, &s);
	s.hash[0] = 0xcbbb9d5dc1059ed8;
	s.hash[1] = 0x629a292a367cd507;
	s.hash[2] = 0x9159015a3070dd17;
	s.hash[3] = 0x152fecd8f70e5939;
	s.hash[4] = 0x67332667ffc00b31;
	s.hash[5] = 0x8eb44a8768581511;
	s.hash[6] = 0xdb0c2e0d64f98fa7;
	s.hash[7] = 0x47b5481dbefa4fa4;
	while (++i < (s.multiples))
		sha64_cycle(i, &s, w, -1);
	to_hash = buf;
	ft_sprintf(to_hash,
		"%.16llx%.16llx%.16llx%.16llx%.16llx%.16llx",
		s.hash[0], s.hash[1], s.hash[2], s.hash[3],
		s.hash[4], s.hash[5]);
	free_message(s.multiples, s.message);
	free(s.message);
	return (to_hash);
}
