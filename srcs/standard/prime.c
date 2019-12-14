/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prime.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 19:01:02 by rpapagna          #+#    #+#             */
/*   Updated: 2019/12/14 01:23:00 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "standard.h"

int				arg_err(int err, char *arg, t_ssl *ssl)
{
	int		i;

	i = 0;
	if (!arg || !arg[i])
		err -= 1;
	else if (arg && arg[i] == '-')
		++i;
	if (!err && !arg[i])
		err = 1;
	while (arg && arg[i] && ++err)
	{
		if (++err && !ft_isdigit(arg[i++]))
		{
			err = 1;
			break ;
		}
	}
	if (err == -1)
		ft_putstr_fd("missing", 2);
	else if (err == 1)
		ft_putstr_fd("invalid", 2);
	else
		ft_putstr_fd("too small", 2);
	ft_putstr_fd(" n argument for -bits\n", 2);
	return (opt_desciption(ssl->type));
}

static int		valid_arg(char **av, t_ssl *ssl, int *i)
{
	if (!ft_strcmp(&av[*i][1], "bits"))
	{
		ssl->flag |= P_BITS;
		ssl->fd[0] = av[*i + 1] && ft_isdigit(av[*i + 1][0]) ?\
		ft_atoull(av[++(*i)]) : -1;
	}
	else if (!ft_strcmp(&av[*i][1], "generate"))
		ssl->flag |= P_GEN;
	else if (!ft_strcmp(&av[*i][1], "hex"))
		ssl->flag |= HEX;
	else
		return (1);
	return (0);
}

int				parse_prime(char **av, t_ssl *ssl, __uint64_t *n, int i)
{
	*n = 0;
	while ((av[++i]))
	{
		if (av[i][0] == '-')
		{
			if (valid_arg(av, ssl, &i))
				return (ft_error(6, &av[i][1], ssl));
		}
		else if (!ft_isdigit(av[i][0]))
			return (ft_error(6, av[i], ssl));
		else if (*n)
		{
			ft_putstr_fd(E_MANY, 2);
			return (opt_desciption(ssl->type));
		}
		else
			*n = ft_atoull(av[i]);
		if (ssl->fd[0] == -1)
			return (arg_err(0, av[i + 1], ssl));
	}
	if (ssl->fd[0] == 64 && ++ssl->fd[0])
		return (0);
	ssl->fd[0] = (ssl->fd[0] == 1 || (ssl->fd[0] && !(ssl->fd[0] % 64)) ||\
	ssl->fd[0] > 64) ? 16 : ssl->fd[0];
	return (0);
}

void			prime_command(char **av, t_ssl *ssl)
{
	__uint64_t	n;

	ssl->flag = 0;
	ssl->fd[0] = 0;
	if (parse_prime(av, ssl, &n, 1))
		;
	else if (!(ssl->flag & P_GEN) && ((!n && ssl->flag & P_BITS) || !av[2]))
	{
		ft_putstr_fd("No prime specified.\n", 2);
		opt_desciption(ssl->type);
	}
	else
	{
		if (ssl->flag & P_GEN)
		{
			if (!ssl->fd[0])
				ft_putstr_fd("Specify the number of bits.\n", 2);
			else
				ft_printf(ssl->flag & HEX ? "%llX\n" : "%llu\n",
				genprime(ssl->fd[0], 1));
		}
		else
			ft_printf(ssl->flag & HEX ? "%llX is %s\n" : "%llu is %s\n", n,
		ft_is_primary(n, 9.0F) ? "prime" : "not prime");
	}
}
