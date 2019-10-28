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

void			ssl_rsa(char **av, t_ssl *ssl)
{
	t_ftbi		*num;
	// __uint64_t	num;
	float		prob;

	if (ssl->type == 31)
	{
		ft_error(1, av[1], ssl);
		return ;
	}
	if (!av[2])
	{
		ssl->flag = '0';
		ft_error(2, av[1], ssl);
		return ;
	}
	// num = strtoull(av[2], 0x0, 10);
	num = ftbi_new_str(av[2]);
	prob = 0.99;
	if (ft_is_primary(num, prob))
		ft_printf("%s is prime at %.0f%% probability.\n", ftbi_tostr(num), prob * 100);
	else
		ft_printf("%s is composite.\n", ftbi_tostr(num));
		// ft_printf("%llu is prime at %.0f%% probability.\n", num, prob * 100);
		// ft_printf("%llu is composite\n", num);
}
