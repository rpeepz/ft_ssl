/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 00:53:07 by rpapagna          #+#    #+#             */
/*   Updated: 2020/01/06 20:24:41 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher.h"

uint64_t	endianflip_64bit(uint64_t val)
{
	return (
		(val & 0x00000000000000FF) << 56 | (val & 0x000000000000FF00) << 40 |
		(val & 0x0000000000FF0000) << 24 | (val & 0x00000000FF000000) << 8 |
		(val & 0x000000FF00000000) >> 8 | (val & 0x0000FF0000000000) >> 24 |
		(val & 0x00FF000000000000) >> 40 | (val & 0xFF00000000000000) >> 56
		);
}

uint64_t	mask_bits(int n)
{
	uint64_t	mask;
	int			i;

	mask = 0;
	i = 0;
	while (i < n)
	{
		mask <<= 1;
		mask += 1;
		i += 1;
	}
	return (mask);
}

uint64_t	join_bits(uint64_t left, uint64_t right, int size)
{
	uint64_t	mask;

	mask = mask_bits(size);
	left = (left & mask) << (64 - size);
	right = (right & mask) << (64 - (size * 2));
	return (left + right);
}

void		split_bits(uint64_t val, int size, uint32_t *left, uint32_t *right)
{
	uint64_t	mask;
	int			half;

	half = size / 2;
	mask = mask_bits(half);
	*left = (val >> (64 - half)) & mask;
	*right = (val >> (64 - (half * 2))) & mask;
}

uint64_t	reorder_bits(uint64_t src, const int *order, int n)
{
	uint64_t		dst;
	int				i;

	dst = 0;
	i = 0;
	while (i < n)
	{
		if ((src << (order[i] - 1)) & 0x8000000000000000)
			dst |= 0x8000000000000000 >> i;
		++i;
	}
	return (dst);
}