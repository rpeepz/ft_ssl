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

	min = 1L << (abs(bits / 2 - 1));
	max = (1L << (bits / 2)) - 1;
	i = 0;
	while (1)
	{
		if (i % (bits * 2) == 0)
		{
			p = (genrand(min, max) | 1) * (genrand(min, max) | 1);
			p |= 1UL << (bits - 1);
		}
		if (ft_is_primary(p, 9.0F))
			break ;
		ft_putchar('.');
		p += 2;
		i++;
	}
	DEBUG ? ft_printf("\nSUCCESS\tprime --> [%llb]\n", p) : ft_putchar('\n');
	return (p);
}

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

__uint64_t		genrsa(t_rsa_out rsa)
{
	t_rsa		gg;

	ft_printf("Generating RSA private key, %d bit long modulus\n", rsa.bits);
	gg.p = genprime(rsa.bits / 2);
	gg.q = genprime(rsa.bits / 2);
	gg.n = gg.p * gg.q;
	gg.e = 65537;
	gg.phi = (gg.p - 1) * (gg.q - 1);
	gg.d = mod_inverse(gg.e, gg.phi);
	gg.dmp1 = gg.d % (gg.p - 1);
	gg.dmq1 = gg.d % (gg.q - 1);
	gg.iqmp = mod_inverse(gg.q, gg.p);
	ft_printf("e is %llu (%#x)\n", gg.e, gg.e);
	rsa_encode_out(rsa, gg);
	return (gg.n);
}
