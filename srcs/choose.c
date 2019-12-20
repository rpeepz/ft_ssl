/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 23:45:13 by rpapagna          #+#    #+#             */
/*   Updated: 2019/12/20 02:18:30 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "cipher.h"
#include "hash.h"
#include "standard.h"

void			ssl_md5(char **av, t_ssl *ssl)
{
	int		i;
	char	*line;

	i = -1;
	line = NULL;
	if (!(ssl->flag & 0x38000) && !ssl->flag && ssl->file_index[0])
		;
	else if (!(ssl->flag & S_FLAG) && (!*(ssl->fd) || ssl->flag & P_FLAG))
	{
		get_stdin(&line, 0, 1, 0);
		line = (!line) ? ft_strdup("") : line;
		ssl->flag &= ~0x40000;
		if (ssl->flag || (ssl->flag && !(ssl->flag & 0x10000)))
			ssl->flag |= 0x8000;
		hash(av[1], line, ssl, 0);
		ft_pipewrench("-s", &line) ? ssl->flag &= ~0x1000 : 0;
	}
	ssl->flag &= ~P_FLAG;
	while (ssl->fd[++i])
	{
		ssl->flag &= ~0x40000;
		hash(av[1], av[ssl->file_index[i]], ssl, i);
	}
}

void			ssl_b64(char **av, t_ssl *ssl)
{
	t_parse		b64;
	uint8_t		buf[64];
	int			len;
	int			i;

	ft_bzero(&b64, sizeof(b64));
	ft_bzero(buf, 64);
	b64.fd_out = 1;
	if (parse_b64(av, &b64, ssl, 1))
		;
	else
	{
		i = 0;
		if (b64.flag & D_FLAG)
			decode_driver(&b64);
		else
		{
			while ((len = read(b64.fd_in, buf, 63)) == 63)
			{
				base64_nstr_fd(buf, len, b64.fd_out, &i);
				ft_bzero(buf, 64);
			}
			base64_nstr_fd(buf, len, b64.fd_out, &i);
		}
	}
}

void			ssl_des(char **av, t_ssl *ssl)
{
	t_parse		des;

	ft_bzero(&des, sizeof(des));
	des.args = ft_memalloc(sizeof(t_des_arg));
	des.fd_out = 1;
	if (parse_des(av, &des, ssl, 1))
		;
	else
	{
		ft_printf("flag\t= [%.8b]\n", des.flag);
		ft_printf("fd in\t= [%d]\n", des.fd_in);
		ft_printf("fd out\t= [%d]\n", des.fd_out);
		ft_printf("iv\t= [%llu]\n", des.args->iv);
		ft_printf("key\t= [%llu]\n", des.args->key);
		ft_printf("pass\t= [%s]\n", des.args->pass);
		ft_printf("salt\t= [%llu]\n", des.args->salt);
		des_process(des, ssl, av[1]);
	}
	ft_strdel(&des.args->pass);
	ft_memdel((void **)&des.args);
}

void			ssl_standard(char **av, t_ssl *ssl)
{
	if (ssl->type == 41 && ft_printf("%s%s", VERSION, COPYRIGHT))
		;
	else if (ssl->type == 42)
		rand_command(av, ssl, 0);
	else if (ssl->type == 43 && opt_desciption(ssl->type))
		;
	(void)av;
}
