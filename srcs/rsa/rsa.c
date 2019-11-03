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

int				check_utl_arg(t_rsa_out *rsa, char *arg)
{
	if (!ft_strcmp(arg, "pubin"))
		rsa->flag |= 0x8;
	else if (!ft_strcmp(arg, "encrypt"))
		rsa->flag |= 0x10;
	else if (!ft_strcmp(arg, "decrypt"))
		rsa->flag |= 0x20;
	else if (!ft_strcmp(arg, "hexdump"))
		rsa->flag |= 0x40;
	else
		return (1);
	return (0);
}

int				check_rsa_arg(t_rsa_out *rsa, char *arg)
{
	if (!ft_strcmp(arg, "text"))
		rsa->flag |= 0x4;
	else if (!ft_strcmp(arg, "noout"))
		rsa->flag |= 0x8;
	else if (!ft_strcmp(arg, "check"))
		rsa->flag |= 0x10;
	else if (!ft_strcmp(arg, "pubin"))
		rsa->flag |= 0x20;
	else if (!ft_strcmp(arg, "pubout"))
		rsa->flag |= 0x40;
	else
		return (1);
	return (0);
}

int				valid_arg(t_ssl *ssl, t_rsa_out *rsa, char *arg, char *filename)
{
	if ((rsa->fd_out == 1) && !ft_strcmp(arg, "out"))
	{
		rsa->flag |= 0x1;
		IF_RETURN(!filename, 1);
	}
	else if (ssl->type == 31)
		return (1);
	else if (!ft_strcmp(arg, "in"))
	{
		rsa->flag |= 0x2;
		IF_RETURN(!filename || open(filename, O_RDONLY) < 3, 1);
	}
	else if (ssl->type == 32)
	{
		if (!ft_strcmp(arg, "inkey"))
		{
			rsa->flag |= 0x4;
			IF_RETURN(!filename || open(filename, O_RDONLY) < 3, 1);
		}
		else if (check_utl_arg(rsa, arg))
			return (1);
	}
	else if (ssl->type == 33)
		IF_RETURN(check_rsa_arg(rsa, arg), 1);
	return (0);
}

int				parse_rsa(char **av, t_ssl *ssl, t_rsa_out *rsa, int i)
{
	while ((av[++i]))
	{
		if (ssl->type == 31 && ft_isdigit(av[i][0]))
			return ((rsa->bits = ft_atoi(av[i])) ? 0 : 0);
		if (av[i][0] == '-')
		{
			if (valid_arg(ssl, rsa, &av[i][1], av[i + 1]))
				return (ft_error(6, &av[i][1], ssl));
			else if (rsa->fd_out == 1 && rsa->flag & 0x1)
				rsa->fd_out = open(av[++i], O_RDWR | O_CREAT, 0644);
			else if (ssl->type > 31 && (!rsa->fd_in) && (rsa->flag & 0x2))
				rsa->fd_in = open(av[++i], O_RDONLY);
			else if (ssl->type == 32 && (!rsa->fd_inkey) && (rsa->flag & 0x4))
				rsa->fd_inkey = open(av[++i], O_RDONLY);
		}
		else
			return (1);
	}
	return (0);
}

void run_output(t_ssl *ssl, t_rsa_out rsa)
{
	ft_printf("ssl flags  [%b]\n", ssl->flag);
	ft_printf("ssl type   [%d]\n", ssl->type);
	ft_printf("rsa bits   [%d]\n", rsa.bits);
	ft_printf("rsa fd in  [%d]\n", rsa.fd_in);
	ft_printf("rsa fd out [%d]\n", rsa.fd_out);
	ft_printf("rsa in key [%d]\n", rsa.fd_inkey);
	ft_printf("rsa flags  [%b]\n", rsa.flag);
	ft_printf("rsa type   [%d]\n", rsa.type);
}

void			ssl_rsa(char **av, t_ssl *ssl)
{
	t_rsa_out	rsa;

	ft_bzero(&rsa, sizeof(t_rsa_out));
	rsa.fd_out = 1;
	if (parse_rsa(av, ssl, &rsa, 1))
	{
		return ;
	}
	rsa.bits = rsa.bits > MAX_BIT_PRIME || !rsa.bits ? MAX_BIT_PRIME : rsa.bits;
	if (ssl->type == 31)
		genrsa(rsa);
	else if (!av[2])
	{
		ssl->flag = 'Z';
		ft_error(6, av[1], ssl);
	}
	else if (ssl->type == 36)
	{
		if (ft_is_primary(ft_atoull(av[2]), 9.0F))
			ft_printf("%llu is prime.\n");
		else
			ft_printf("%llu is composite.\n", ft_atoull(av[2]));
	}
	DEBUG ? run_output(ssl, rsa) : 0;
}
