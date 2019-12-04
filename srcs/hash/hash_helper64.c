/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_helper64.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 21:28:37 by rpapagna          #+#    #+#             */
/*   Updated: 2019/11/17 21:55:22 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"

__uint64_t		rr(__uint64_t a, __uint64_t b)
{
	return (((a) >> (b)) | ((a) << (64 - (b))));
}

__uint64_t		e0(__uint64_t x)
{
	return (rr(x, 28) ^ rr(x, 34) ^ rr(x, 39));
}

__uint64_t		e1(__uint64_t x)
{
	return (rr(x, 14) ^ rr(x, 18) ^ rr(x, 41));
}

__uint64_t		s0(__uint64_t x)
{
	return (rr(x, 1) ^ rr(x, 8) ^ ((x) >> 7));
}

__uint64_t		s1(__uint64_t x)
{
	return (rr(x, 19) ^ rr(x, 61) ^ ((x) >> 6));
}
