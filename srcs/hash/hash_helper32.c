/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_helper32.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 21:28:37 by rpapagna          #+#    #+#             */
/*   Updated: 2019/11/17 21:55:22 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"

__uint32_t		rr32(__uint32_t a, __uint32_t b)
{
	return (((a) >> (b)) | ((a) << (32 - (b))));
}

__uint32_t		e0_32(__uint32_t x)
{
	return (rr32(x, 2) ^ rr32(x, 13) ^ rr32(x, 22));
}

__uint32_t		e1_32(__uint32_t x)
{
	return (rr32(x, 6) ^ rr32(x, 11) ^ rr32(x, 25));
}

__uint32_t		s0_32(__uint32_t x)
{
	return (rr32(x, 7) ^ rr32(x, 18) ^ ((x) >> 3));
}

__uint32_t		s1_32(__uint32_t x)
{
	return (rr32(x, 17) ^ rr32(x, 19) ^ ((x) >> 10));
}