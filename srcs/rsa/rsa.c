/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 18:59:43 by rpapagna          #+#    #+#             */
/*   Updated: 2019/10/31 23:37:25 by rpapagna         ###   ########.fr       */
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

void			parse_rsa(char **av, t_ssl *ssl)
{
	if (av[2])
		(void)ssl;
}

void			ssl_rsa(char **av, t_ssl *ssl)
{
	__uint64_t	num;
	float		prob;

	parse_rsa(av, ssl);
	if (ssl->type == 31)
	{
		num = genrsa(ssl, av[2] ? ft_atoi(av[2]) : 0);
		return ;
	}
	if (!av[2])
	{
		ssl->flag = 'P';
		ft_error(2, av[1], ssl);
		return ;
	}
	num = ft_atoull(av[2]);
	prob = 0.99;
	if (ft_is_primary(num, prob))
		ft_printf("%llu is prime at %.0f%% probability.\n", num, prob * 100);
	else
		ft_printf("%llu is composite\n", num);
}
