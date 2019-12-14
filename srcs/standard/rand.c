/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rand.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 19:43:06 by rpapagna          #+#    #+#             */
/*   Updated: 2019/12/14 02:25:33 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "standard.h"
#include "encode.h"

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
	fd = open(RAND_DIR, O_RDONLY);
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

void			do_rand(t_ssl *ssl, int bytes)
{
	__uint64_t	n;
	uint8_t		buf[PAGESIZE];

	ft_bzero(buf, PAGESIZE);
	if (bytes <= 0 || bytes > 8)
	{
		opt_desciption(ssl->type);
		return ;
	}
	n = genrand(1ULL << (abs(bytes * 8) - 8), UINT64_MAX >> (64 - bytes * 8));
	if (ssl->flag & HEX)
	{
		ft_sprintf((char *)buf, "%0*llx\n", bytes * 2, n);
		ft_putstr_fd((char *)buf, ssl->fd[1]);
	}
	else if (ssl->flag & RAND_BASE64)
		base64_nstr_fd(byte_string(buf, n), byte_len(n), ssl->fd[1]);
	else
	{
		ft_sprintf((char *)buf, "%llu\n", n);
		ft_putstr_fd((char *)buf, ssl->fd[1]);
	}
	ssl->fd[1] > 1 ? close(ssl->fd[1]) : 0;
}

static int		valid_rand_arg(char **av, t_ssl *ssl, int *i, char *fname)
{
	if (!ft_strcmp(&av[*i][1], "base64"))
		ssl->flag |= RAND_BASE64;
	else if (!ft_strcmp(&av[*i][1], "hex"))
		ssl->flag |= HEX;
	else if (ssl->fd[1] == 1 && !ft_strcmp(&av[*i][1], "out"))
	{
		ssl->flag |= RAND_OUT;
		if (!fname && (ssl->fd[1] = -1))
			ft_putstr_fd("missing file argument for -out\n", 2);
		return (!fname ? 1 : 0);
	}
	else
		return (1);
	return (0);
}

int				parse_rand(char **av, t_ssl *ssl, int *bytes, int i)
{
	while (av[++i])
	{
		if (av[i][0] == '-')
		{
			if (valid_rand_arg(av, ssl, &i, av[i + 1]))
				return (ssl->fd[1] == -1 ? opt_desciption(ssl->type) :\
				ft_error(6, &av[i][1], ssl));
		}
		else if (!ft_isdigit(av[i][0]))
			return (ft_error(6, av[i], ssl));
		else if (*bytes || (ssl->flag & RAND_BASE64 && ssl->flag & HEX))
		{
			ft_putstr_fd(E_MANY, 2);
			return (opt_desciption(ssl->type) && (*bytes = 1));
		}
		else
			*bytes = ft_atoi(av[i]);
	}
	if (!*bytes || (ssl->flag & RAND_BASE64 && ssl->flag & HEX))
	{
		ssl->flag & RAND_BASE64 && ssl->flag & HEX ?\
		ft_putstr_fd(E_MANY, 2) : 0;
		return (1 && !(*bytes = 0));
	}
	return (0);
}

void			rand_command(char **av, t_ssl *ssl, int bytes)
{
	int		ret;

	ssl->flag = 0;
	ssl->fd[1] = 1;
	if (!av[2] || (ret = parse_rand(av, ssl, &bytes, 1)))
	{
		if (((ssl->flag & RAND_BASE64 && ssl->flag & HEX) ||\
		ssl->flag & RAND_OUT) && bytes)
			;
		else if (ret != -1 && !bytes)
		{
			ft_putstr_fd("Specify the number of bytes.\n", 2);
			opt_desciption(ssl->type);
		}
	}
	else
		do_rand(ssl, bytes);
}
