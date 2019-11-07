/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:07:02 by rpapagna          #+#    #+#             */
/*   Updated: 2019/11/04 23:30:37 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

__uint64_t		mod_inverse(__uint64_t a, __uint64_t b)
{
	__uint64_t	b0;
	__int64_t	t;
	__uint64_t	q;
	__int64_t	x0;
	__int64_t	x1;

	b0 = b;
	x0 = 0;
	x1 = 1;
	IF_RETURN(a == b, 0);
	while (a > 1)
	{
		!b ? ft_putendl_fd("Error divide by 0", 2) : 0;
		IF_THEN(!b, exit(0));
		q = a / b;
		t = b;
		b = a % b;
		a = t;
		t = x0;
		x0 = x1 - q * x0;
		x1 = t;
	}
	if (x1 < 0)
		x1 += b0;
	return (x1);
}

__uint64_t		safe_modpow(__uint64_t b, __uint64_t c, __uint64_t mod)
{
	__uint64_t	two_bc;

	two_bc = (2 * (b * c)) % mod;
	b = (b * b) % mod;
	c = (c * c) % mod;
	return (b + two_bc + c);
}

__uint64_t		modpow(__uint64_t num, __uint64_t exp, __uint64_t mod)
{
	__uint64_t	x;

	if (mod < 2 || num == 0)
	{
		if (mod == 0)
			write(2, "Cannot take modpow with modulus 0\n", 34);
		return (0);
	}
	if (exp == 0)
		return (1);
	x = 1;
	num = num % mod;
	while (exp > 0)
	{
		if (exp & 0x1)
			x = (x * num) % mod;
		exp /= 2;
		if (num <= UINT32_MAX)
			num = (num * num) % mod;
		else
			num = safe_modpow((num & 0xFFFFFFFF00000000) >> 32,
			num - ((num & 0xFFFFFFFF00000000) >> 32) & 0xFFFFFFFF, mod);
	}
	return (x);
}
