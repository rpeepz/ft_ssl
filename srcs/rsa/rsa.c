/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 18:59:43 by rpapagna          #+#    #+#             */
/*   Updated: 2019/10/12 20:06:27 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft_ssl.h"
#include <stdio.h>

/*
**	int				lazy_prime(__uint64_t n, t_primary checks)
**	{
**		uint64_t	i;
**
**		ft_printf("d= %llu\n", checks.d);
**		i = 2;
**		while (i < n)
**		{
**			if (n % i == 0)
**				return (0);
**			i++;
**		}
**		return (1);
**	}
*/

__uint64_t		hex_to_ull(unsigned char *x, int len)
{
	__uint64_t	p;
	int			i;

	p = 0;
	i = 0;
	while (i < len)
	{
		p += x[i] << ((8 * (8 - i)) - 8);
		i++;
	}
	return (p);
}

void			genprime(char *bits)
{
	__uint64_t			min;
	__uint64_t			max;
	__uint64_t			p;
	unsigned char		buf[9];
	int					fd;

	(void)bits;
	// if (bits)
	// {
	// 	min = bigint(2 ^ (bits - 1));
	// 	max = bigint((2 ^ bits) - 1);
	// }
	min = 0x8000000000000000;
	max = 0xFFFFFFFFFFFFFFFF;
	fd = open("/dev/urandom", O_RDONLY);
	while (1)
	{
		ft_bzero(buf, 8);
		read(fd, buf, 8);
		buf[8] = 0;
		p = hex_to_ull(buf, 8);
		if (!(p & 0x1) || p < min)
			continue ;
		printf("generated potential --> [%llu]\n", p);
		if (ft_is_primary(p, 9.0F))
			break ;
		printf("FAILED...\n");
	}
	printf("your prime is ready...\n[%llu]\n", p);
}

void			ssl_rsa(char **av, t_ssl *ssl)
{
	__uint64_t	num;
	float		prob;

	//parse_rsa(av, ssl);
	if (ssl->type == 31)
	{
		// ft_error(1, av[1], ssl);
		genprime(av[2]);
		return ;
	}
	if (!av[2])
	{
		ssl->flag = 'P';
		ft_error(2, av[1], ssl);
		return ;
	}
	num = strtoull(av[2], 0x0, 10);
	prob = 0.99;
	if (ft_is_primary(num, prob))
		ft_printf("%llu is prime at %.0f%% probability.\n", num, prob * 100);
	else
		ft_printf("%llu is composite\n", num);
}
