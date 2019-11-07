/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa_out.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 18:41:24 by rpapagna          #+#    #+#             */
/*   Updated: 2019/11/05 02:11:59 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"
#include "encode.h"

void			debug_output(t_ssl *ssl, t_rsa_out rsa)
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

void			rsa_text_out(t_rsa_out rsa, t_rsa gg)
{
	char	buf[PAGESIZE];

	ft_bzero(buf, PAGESIZE);
	ft_sprintf(buf, "Private-Key: (%d bit)\n", rsa.bits);
	ft_sprintf(&buf[LEN(buf)], "modulus: %llu (%#llx)\n", gg.n, gg.n);
	ft_sprintf(&buf[LEN(buf)], "publicExponent: %llu (%#llx)\n", gg.e, gg.e);
	ft_sprintf(&buf[LEN(buf)], "privateExponent: %llu (%#llx)\n", gg.d, gg.d);
	ft_sprintf(&buf[LEN(buf)], "prime1: %llu (%#llx)\n", gg.p, gg.p);
	ft_sprintf(&buf[LEN(buf)], "prime2: %llu (%#llx)\n", gg.q, gg.q);
	ft_sprintf(&buf[LEN(buf)], "exponent1: %llu (%#llx)\n", gg.dmp1, gg.dmp1);
	ft_sprintf(&buf[LEN(buf)], "exponent2: %llu (%#llx)\n", gg.dmq1, gg.dmq1);
	ft_sprintf(&buf[LEN(buf)], "coefficient: %llu (%#llx)\n", gg.iqmp, gg.iqmp);
	ft_putstr_fd(buf, rsa.fd_out);
}

// void			base64_llu_fd(__uint64_t n, int fd)
// {
// 	__uint64_t	edata;

	
// 	ft_printf("[%llx/%llb]\n", n, n);

// }
int			byte_len(__uint64_t n)
{
	int	len;

	len = 0;
	while (n)
	{
		len++;
		n >>= 8;
	}
	return (len);
}

#define SEQUENCE '\x30'
#define INT '\x02'
#define VERSION "\x01\x00"
void			rsa_encode_out(t_rsa_out rsa, t_rsa gg)
{
	char	buf[PAGESIZE];
	int	bytes;

	ft_bzero(buf, PAGESIZE);
	ft_putstr_fd("-----BEGIN RSA PRIVATE KEY-----\n", rsa.fd_out);
	//put base64
	ft_printf("%x%s\n\n", byte_len(gg.e), num_string_u_base(gg.e, 16));
//	base64_str_fd("any carnal pleasure.", rsa.fd_out);
	bytes = ft_sprintf(buf,
	"%c%s%c%c%s%c%c%s%c%c%s%c%c%s%c%c%s%c%c%s%c%c%s%c%c%s", INT, VERSION,
	INT, byte_len(gg.n), num_string_u_base(gg.n, 10),
	INT, byte_len(gg.e), num_string_u_base(gg.e, 10),
	INT, byte_len(gg.d), num_string_u_base(gg.d, 10),
	INT, byte_len(gg.p), num_string_u_base(gg.p, 10),
	INT, byte_len(gg.q), num_string_u_base(gg.q, 10),
	INT, byte_len(gg.dmp1), num_string_u_base(gg.dmp1, 10),
	INT, byte_len(gg.dmq1), num_string_u_base(gg.dmq1, 10),
	INT, byte_len(gg.iqmp), num_string_u_base(gg.iqmp, 10));
	ft_printf("[%d]\n", LEN(buf));
	ft_printf("[%d]\n", bytes);
	ft_sprintf(buf, "%c%c%c%s\n", SEQUENCE, bytes, bytes, buf);
	base64_str_fd(buf, rsa.fd_out);
	ft_putstr_fd("\n", rsa.fd_out);
	// base64_llu_fd(gg.e, rsa.fd_out);
	ft_putstr_fd("-----END RSA PRIVATE KEY-----\n", rsa.fd_out);
	rsa_text_out(rsa, gg);
}
