/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa_out.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 18:41:24 by rpapagna          #+#    #+#             */
/*   Updated: 2019/11/12 18:15:03 by rpapagna         ###   ########.fr       */
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

void			rsa_encode_out(t_rsa_out rsa, t_rsa gg)
{
	char	buf[PAGESIZE];
	int	bytes;

	ft_bzero(buf, PAGESIZE);
	ft_putstr_fd("-----BEGIN RSA PRIVATE KEY-----\n", rsa.fd_out);
	//put base64
	// base64_str_fd("any carnal pleasure.", rsa.fd_out);
	bytes = ft_sprintf(buf,
	"%02x%02x%0*llx%02x%02x%0*llx%02x%02x%0*llx%02x%02x%0*llx%02x%02x%0*llx",
	INT, byte_len(gg.n), byte_len(gg.n) * 2, gg.n,
	INT, byte_len(gg.e), byte_len(gg.e) * 2, gg.e,
	INT, byte_len(gg.d), byte_len(gg.d) * 2, gg.d,
	INT, byte_len(gg.p), byte_len(gg.p) * 2, gg.p,
	INT, byte_len(gg.q), byte_len(gg.q) * 2, gg.q);
	bytes += ft_sprintf(&buf[LEN(buf)],
	"%02x%02x%0*llx%02x%02x%0*llx%02x%02x%0*llx",
	INT, byte_len(gg.dmp1), byte_len(gg.dmp1) * 2, gg.dmp1,
	INT, byte_len(gg.dmq1), byte_len(gg.dmq1) * 2, gg.dmq1,
	INT, byte_len(gg.iqmp), byte_len(gg.iqmp) * 2, gg.iqmp);
	base64_str_fd(buf, rsa.fd_out);
	ft_putstr_fd("\n", rsa.fd_out);
	// base64_llu_fd(gg.e, rsa.fd_out);
	ft_putstr_fd("-----END RSA PRIVATE KEY-----\n", rsa.fd_out);
	rsa_text_out(rsa, gg);
}
