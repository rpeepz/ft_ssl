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
	if (a == b)
		return (0);
	while (a > 1)
	{
		!b ? ft_putendl_fd("Error divide by 0", 2) : 0;
		if (!b)
			exit(0);
		q = a / b;
		t = b;
		b = a % b;
		a = t;
		t = x0;
		x0 = x1 - q * x0;
		x1 = t;
	}
	return (x1 < 0 ? x1 += b0 : x1);
}

/*
**	following function only works when m is 63 bits or less
**
**	uint64_t	mod_mul(uint64_t a, uint64_t b, uint64_t mod)
**	{
**		uint64_t	res;
**
**		res = 0;
**		a = a % mod;
**		while (b)
**		{
**	    	if (b & 1)
**				res = (res + a) % mod;
**	    	a = (a << 1) % mod;
**	    	b >>= 1;
**	    }
**	    return (res);
**	}
**
**	below function works even if m is 64 bits
*/

__uint64_t		mulmod(__uint64_t a, __uint64_t b, __uint64_t m)
{
	__uint64_t	res;
	__uint64_t	temp_b;

	res = 0;
	if (b >= m)
		b = (m > UINT64_MAX >> 1) ? b - m : b % m;
	while (a)
	{
		if (a & 1)
		{
			if (b >= m - res)
				res -= m;
			res += b;
		}
		a >>= 1;
		temp_b = b;
		if (b >= m - b)
			temp_b -= m;
		b += temp_b;
	}
	return (res);
}

__uint64_t		powmod(__uint64_t num, __uint64_t exp, __uint64_t mod)
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
	while (exp)
	{
		if (exp & 1)
			x = mulmod(x, num, mod);
		num = mulmod(num, num, mod);
		exp >>= 1;
	}
	return (x);
}

/*
**	function to take the modulo after squaring with helper
**	not needed after finding `mulmod`
**
**	uint64_t addmod(uint64_t x, uint64_t y, uint64_t n)
**	{
**	    // Precondition: x<n, y<n
**	    // If it will overflow, use alternative calculation
**	    if (x + y <= x) x = x - (n - y);
**	    else x = (x + y) % n;
**	    return x;
**	}
**
**	uint64_t	sqrmod(uint64_t a, uint64_t n)
**	{
**	    uint64_t b;
**	    uint64_t sum = 0;
**
**	    // Make sure original number is less than n
**	    a = a % n;
**	    // Use double and add algorithm to calculate a*a mod n
**	    for (b = a; b != 0; b >>= 1) {
**	        if (b & 1) {
**	            sum = addmod(sum, a, n);
**	        }
**	        a = addmod(a, a, n);
**	    }
**	    return sum;
**	}
*/
