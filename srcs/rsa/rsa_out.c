/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa_out.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 18:41:24 by rpapagna          #+#    #+#             */
/*   Updated: 2019/11/16 18:00:02 by rpapagna         ###   ########.fr       */
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

void			rsa_encode_out(t_rsa_out rsa, t_rsa gg)
{
	int			len;
	int			i;
	uint8_t		buf[PAGESIZE];
	uint8_t		buf2[10];

	ft_bzero(buf, PAGESIZE);
	ft_bzero(buf2, 10);
	len = 0;
	i = 0;
	//need to find a better way to encode 00 in asn1
	asn1(gg, buf, buf2, &len);
	while (i < len)
	{
		if (buf[i] == 0xFF)
			buf[i] = 0x00;
		i++;
	}
	ft_putstr_fd(PRIV_BEGIN_HEADER, rsa.fd_out);
	base64_nstr_fd((char*)buf, len, rsa.fd_out);
	ft_putstr_fd(PRIV_END_HEADER, rsa.fd_out);
	rsa_text_out(rsa, gg);
	close(rsa.fd_out);
}
