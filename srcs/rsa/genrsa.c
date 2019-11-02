/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   genrsa.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 22:56:10 by rpapagna          #+#    #+#             */
/*   Updated: 2019/10/31 23:39:06 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft_ssl.h"

__uint64_t		genrand(__uint64_t min, __uint64_t max)
{
	int				fd;
	int				bytes;
	__uint64_t		tmp;
	unsigned char	*buf;

	tmp = max;
	bytes = 0;
	while (tmp && ++bytes)
		tmp >>= 8;
	buf = ft_memalloc(sizeof(unsigned char) * (bytes + 1));
	fd = open("/dev/urandom", O_RDONLY);
	while (1)
	{
		ft_bzero(buf, bytes);
		read(fd, buf, bytes);
		ft_memcpy(&tmp, buf, bytes);
		if (tmp >= min && tmp <= max)
			break ;
	}
	close(fd);
	free(buf);
	return (tmp);
}

__uint64_t		genprime(int bits)
{
	__uint64_t			p;
	__uint64_t			min;
	__uint64_t			max;
	unsigned int		i;

	if (bits <= 0 || bits > 64)
		bits = 64;
	min = 1L << (abs(bits / 2 - 1));
	max = (1L << (bits / 2)) - 1;
	i = 0;
	while (1)
	{
		if (i % (bits * 2) == 0)
		{
			ft_printf("Generating %d-bit prime:\n", bits);
			p = (genrand(min, max) | 1) * (genrand(min, max) | 1);
			p |= 1UL << (bits - 1);
		}
		ft_printf("generated potential --> [%llb] ", p);
		if (ft_is_primary(p, 9.0F))
			break ;
		ft_printf("FAILED...\n");
		p += 2;
		i++;
	}
	ft_printf("SUCCESS\n");
	return (p);
}

__uint64_t		lcm(__uint64_t a, __uint64_t b)
{
	while (!(a & 0x1) && !(b & 0x1))
	{
		a /= 2;
		b /= 2;
	}
	return (a * b);
}

// __uint64_t		gcd_extended(__uint64_t a, __uint64_t b, __uint64_t *x, __uint64_t *y)
// {
// 	__uint64_t	x1;
// 	__uint64_t	y1;
// 	__uint64_t	gcd;
// 	if (a == 0)
// 	{
// 		*x = 0, *y = 1;
// 		return b;
// 	}
// 	gcd = gcd_extended(b % a, a, &x1, &y1);
// 	*x = y1 - (b / a) * x1;
// 	*y = x1;
// 	return gcd;
// }

// __uint64_t		mod_inverse(__uint64_t a, __uint64_t m)
// {
// 	__uint64_t	x;
// 	__uint64_t	y;
// 	__uint64_t	g;
// 	__uint64_t	res;
// 	g = gcd_extended(a, m, &x, &y);
// 	if (g != 1)
// 	{
// 		ft_putendl_fd("Inverse doesn't exist", 2);
// 		return (1);
// 	}
// 	else
// 	{
// 		res = ((x % m) + m) % m; 
//     }
// 	return (res);
// }

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
	while (a > 1)
	{
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

__uint64_t		genrsa(t_ssl *ssl, int bits)
{
	t_rsa		gg;

	(void)ssl;
	gg.p = genprime(bits);
	gg.q = genprime(bits);
	gg.n = gg.p * gg.q;
	gg.e = 65537;

	gg.phi = lcm(gg.p - 1, gg.q - 1);
	ft_printf("\n-----1-- phi = %llu -------\n", gg.phi);
	gg.d = (1 + (2 * gg.phi)) / gg.e;
	ft_printf("\n-----1-- d = %llu -------\n", gg.d);
	gg.d = mod_inverse(gg.e, gg.phi);
	ft_printf("\n-----2-- d = %llu -------\n", gg.d);
	
	gg.phi = (gg.p - 1 * gg.q - 1);
	ft_printf("\n-----2-- phi = %llu -------\n", gg.phi);
	gg.d = (1 + (2 * gg.phi)) / gg.e;
	ft_printf("\n-----1-- d = %llu -------\n", gg.d);
	gg.d = mod_inverse(gg.e, gg.phi);
	ft_printf("\n-----2-- d = %llu -------\n", gg.d);
	
	ft_printf("\n~~~~~~~~~~~~~~~~~\n");
	ft_printf("\n------- p = %llu -------\n", gg.p);
	ft_printf("\n------- q = %llu -------\n", gg.q);
	ft_printf("\n------- n = %llu -------\n", gg.n);
	ft_printf("\n------- phi = %llu -------\n", gg.phi);
	ft_printf("\n------- e = %llu -------\n", gg.e);
	ft_printf("\n------- d = %llu -------\n", gg.d);
	return (gg.n);
}