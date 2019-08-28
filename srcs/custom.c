/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 07:10:18 by rpapagna          #+#    #+#             */
/*   Updated: 2019/08/28 01:56:17 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ssl.h"

void		shift(uint64_t *num)
{
	if (num[0] < 0xFFFFFFFFFFFFFF)
		num[0] = num[0] << 7;
	if (num[1] < 0xFFFFFFFFFFFFFF)
		num[1] = num[1] << 7;
	if (num[2] < 0xFFFFFFFFFFFFFF)
		num[2] = num[2] << 7;
	if (num[3] < 0xFFFFFFFFFFFFFF)
		num[3] = num[3] << 7;
}

void		cycler(char *to_hash, uint64_t *cycle, uint64_t *state)
{
	int			i;
	int			prime[4];

	prime[0] = 1198867;
	prime[1] = 1308887;
	prime[2] = 1634177;
	prime[3] = 1826291;
	ft_bzero(cycle, sizeof(cycle));
	i = -1;
	while (++i <= LEN(to_hash))
	{
		cycle[0] += prime[0] * pow(to_hash[i] + to_hash[i + 1], 4);
		cycle[1] += prime[1] * pow(to_hash[i + 1] + to_hash[i], 3);
		cycle[2] += prime[2] * pow(to_hash[i + 2] + to_hash[i + 1], 2);
		cycle[3] += prime[3] * pow(to_hash[i + 3] - to_hash[i], 1);
	}
	state[0] += cycle[0] * prime[0];
	state[1] += cycle[1] * prime[1];
	state[2] += cycle[2] * prime[2];
	state[3] += cycle[3] * prime[3];
}

char		*custom(char *buf, char *to_hash)
{
	uint64_t	cycle[4];
	uint64_t	state[4];
	char		inter[64];
	int			len;

	state[0] = 0xA1041B36;
	state[1] = 0x544B2A10;
	state[2] = 0xB8517961;
	state[3] = 0x170A2F2C;
	while ((len = LEN(to_hash)) > 64)
	{
		ft_bzero(inter, 65);
		cycler(ft_strncpy(inter, to_hash, 64), cycle, state);
		to_hash += 64;
	}
	cycler(ft_strcpy(inter, to_hash), cycle, state);
	to_hash = buf;
	ft_sprintf(buf, "%llx%llx%llx%llx", state[3], state[2], state[1], state[0]);
	return (buf);
}
