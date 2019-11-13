/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa_out.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 18:41:24 by rpapagna          #+#    #+#             */
/*   Updated: 2019/11/13 14:38:23 by rpapagna         ###   ########.fr       */
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

char			byte_len(__uint64_t n)
{
	char	len;

	len = 0;
	while (n)
	{
		len++;
		n >>= 8;
	}
	return (len);
}

unsigned char	*byte_string(unsigned char *buf, __uint64_t n)
{
	int		i;
	int		p;
	int		trig;

	i = 0;
	p = 0;
	trig = 0;
	ft_bzero(buf, 10);
	while (i < 8)
	{
		if (trig || (n & (0xFF << 8 * (7 - i))) >> 8 * (7 - i))
		{
			buf[p] = ((n & (0xFF << 8 * (7 - i))) >> 8 * (7 - i));
			if (!trig && (buf[p] & 0x80))
			{
				buf[p + 1] = buf[p];
				buf[p++] = 0xFF;
			}
			if (!buf[p])
				buf[p] = 0xFF;
			p++;
			trig = 1;
		}
		i++;
	}
	// for (int x = 0; x < 8; x++) {
	// 	ft_printf("[%02x]", buf[x]);
	// }
	// 	ft_printf("\n[%s]\n", buf);
	return (buf);
}

void			dump_to_buf(char *buf, char c, unsigned char *s, int *len)
{
	int		i;
	int		n;

	if (!s)
	{
		buf[*len] = c;
		++(*len);
	}
	else
	{
		i = 0;
		n = LEN((char*)s);
		while (i < n || s[n])
		{
			buf[*len] = s[i];
			++(*len);
			++i;
		}
			// ft_printf("\n");
		// ft_sprintf(&buf[*len], "%s", s);
		// if ((unsigned char)buf[*len] == 0xFF)
		// 	buf[*len] = 0x00;
		// (*len) += LEN((char*)s);
	}
}

void			rsa_encode_out(t_rsa_out rsa, t_rsa gg)
{
	int				len;
	char			buf[PAGESIZE];
	unsigned char	buf2[10];

	ft_bzero(buf, PAGESIZE);
	len = 0;
	ft_putstr_fd("-----BEGIN RSA PRIVATE KEY-----\n", rsa.fd_out);
	//put base64
	// base64_str_fd("any carnal pleasure.", rsa.fd_out);
	dump_to_buf(buf, INT, NULL, &len);
	dump_to_buf(buf, byte_string(buf2, gg.n)[0] == 0xFF ?
	byte_len(gg.n) + 1 : byte_len(gg.n), NULL, &len);
	dump_to_buf(buf, 0, byte_string(buf2, gg.n), &len);
	dump_to_buf(buf, INT, NULL, &len);
	dump_to_buf(buf, byte_len(gg.e), NULL, &len);
	dump_to_buf(buf, 0, byte_string(buf2, gg.e), &len);
	dump_to_buf(buf, INT, NULL, &len);
	dump_to_buf(buf, byte_string(buf2, gg.d)[0] == 0xFF ?
	byte_len(gg.d) + 1 : byte_len(gg.d), NULL, &len);
	dump_to_buf(buf, 0, byte_string(buf2, gg.d), &len);
	dump_to_buf(buf, INT, NULL, &len);
	dump_to_buf(buf, byte_string(buf2, gg.p)[0] == 0xFF ?
	byte_len(gg.p) + 1 : byte_len(gg.p), NULL, &len);
	dump_to_buf(buf, 0, byte_string(buf2, gg.p), &len);
	dump_to_buf(buf, INT, NULL, &len);
	dump_to_buf(buf, byte_string(buf2, gg.q)[0] == 0xFF ?
	byte_len(gg.q) + 1 : byte_len(gg.q), NULL, &len);
	dump_to_buf(buf, 0, byte_string(buf2, gg.q), &len);
	dump_to_buf(buf, INT, NULL, &len);
	dump_to_buf(buf, byte_string(buf2, gg.dmp1)[0] == 0xFF ?
	byte_len(gg.dmp1) + 1 : byte_len(gg.dmp1), NULL, &len);
	dump_to_buf(buf, 0, byte_string(buf2, gg.dmp1), &len);
	dump_to_buf(buf, INT, NULL, &len);
	dump_to_buf(buf, byte_string(buf2, gg.dmq1)[0] == 0xFF ?
	byte_len(gg.dmq1) + 1 : byte_len(gg.dmq1), NULL, &len);
	dump_to_buf(buf, 0, byte_string(buf2, gg.dmq1), &len);
	dump_to_buf(buf, INT, NULL, &len);
	dump_to_buf(buf, byte_string(buf2, gg.iqmp)[0] == 0xFF ?
	byte_len(gg.iqmp) + 1 : byte_len(gg.iqmp), NULL, &len);
	dump_to_buf(buf, 0, byte_string(buf2, gg.iqmp), &len);

	// ft_sprintf(buf, "%c%c%s%c%c%s%c%c%s%c%c%s%c%c%s%c%c%s%c%c%s%c%c%s",
	// INT, byte_len(gg.n), byte_string(buf2, gg.n),
	// INT, byte_len(gg.e), byte_string(buf2, gg.e),
	// INT, byte_len(gg.d), byte_string(buf2, gg.d),
	// INT, byte_len(gg.p), byte_string(buf2, gg.p),
	// INT, byte_len(gg.q), byte_string(buf2, gg.q),
	// INT, byte_len(gg.dmp1), byte_string(buf2, gg.dmp1),
	// INT, byte_len(gg.dmq1), byte_string(buf2, gg.dmq1),
	// INT, byte_len(gg.iqmp), byte_string(buf2, gg.iqmp));

	base64_str_fd(buf, rsa.fd_out);
	ft_putstr_fd("\n", rsa.fd_out);
	// base64_llu_fd(gg.e, rsa.fd_out);
	ft_putstr_fd("-----END RSA PRIVATE KEY-----\n", rsa.fd_out);
	rsa_text_out(rsa, gg);
}
