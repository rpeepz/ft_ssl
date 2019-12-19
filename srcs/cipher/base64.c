/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 01:56:02 by rpapagna          #+#    #+#             */
/*   Updated: 2019/12/18 20:00:03 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher.h"

unsigned char	g_base64[64] =
{
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
	'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd',
	'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
	't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7',
	'8', '9', '+', '/'
};

unsigned char	g_base64_decode[123] =
{
	' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
	' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
	' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 62, ' ',
	' ', ' ', 63, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, ' ', ' ',
	' ', ' ', ' ', ' ', ' ', 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
	10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
	25, ' ', ' ', ' ', ' ', ' ', ' ', 26, 27, 28, 29, 30, 31, 32, 33,
	34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48,
	49, 50, 51
};

/*
**	No padding on ASN1
**	ft_putchar_fd(g_base64[enc[2]], fd);
**	ft_putchar_fd(g_base64[enc[3]], fd);
*/

void			base64_nstr_fd(uint8_t *in, int len, int fd, int *count)
{
	int			i;
	uint8_t		enc[4];

	i = 0;
	while (count ? in[i] : i < len)
	{
		DEBUG ? ft_printf("%02x %02x %02x\n", in[i], in[i + 1], in[i + 2]) : 0;
		ft_bzero(enc, 4);
		enc[0] |= in[i] >> 2;
		enc[1] |= ((in[i] & 0x03) << 4);
		enc[1] |= (in[i + 1] >> 4);
		enc[2] |= ((in[i + 1] & 0x0F) << 2);
		enc[2] |= (in[i + 2] >> 6);
		enc[3] |= (in[i + 2] & 0x3F);
		ft_putchar_fd(g_base64[enc[0]], fd);
		ft_putchar_fd(g_base64[enc[1]], fd);
		ft_putchar_fd((!enc[2] && len - i < 2) ? '=' : g_base64[enc[2]], fd);
		ft_putchar_fd((!enc[3] && len - i < 3) ? '=' : g_base64[enc[3]], fd);
		i += 3;
		count ? (*count) += 4 : 0;
		count && *count % 64 == 0 ? ft_putchar_fd('\n', fd) : 0;
		!count && (i % 48) == 0 ? ft_putchar_fd('\n', fd) : 0;
	}
	!count && (i % 48) ? ft_putchar_fd('\n', fd) : 0;
	count && len < 63 ? ft_putchar_fd('\n', fd) : 0;
}

int				base64_decode(uint8_t *enc, uint8_t *dec, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		if ((i + 4) % 64 == 0)
		{
			if (len != 65)
				i++;
			if (i == len)
				return (i - 1);
		}
		dec[3 * (i / 4)] |= (g_base64_decode[enc[i]]) << 2;
		dec[3 * (i / 4)] |= ((g_base64_decode[enc[i + 1]] & 0x30) >> 4);
		dec[3 * (i / 4) + 1] |= ((g_base64_decode[enc[i + 1]] & 0x0F) << 4);
		if (enc[i + 2] != '=')
			dec[3 * (i / 4) + 1] |= (g_base64_decode[enc[i + 2]] >> 2);
		if (enc[i + 2] != '=')
			dec[3 * (i / 4) + 2] |= (g_base64_decode[enc[i + 2]] << 6);
		if (enc[i + 3] != '=')
			dec[3 * (i / 4) + 2] |= g_base64_decode[enc[i + 3]];
		i += 4;
	}
	return (i);
}

void			decode_driver(t_parse *b64)
{
	uint8_t		buf[66];
	uint8_t		dec[50];
	int			len;

	ft_bzero(buf, 66);
	ft_bzero(dec, 50);
	while ((len = read(b64->fd_in, buf, 65)) == 65)
	{
		buf[ft_strchri((char *)buf, '\n')] = 0;
		base64_decode(buf, dec, len);
		dec[(len / 4) * 3] = 0;
		ft_putstr_fd((char *)dec, b64->fd_out);
		ft_bzero(buf, 65);
		ft_bzero(dec, 49);
	}
	buf[ft_strchri((char *)buf, '\n')] = 0;
	base64_decode(buf, dec, len);
	dec[(int)((float)(len * 2) / 3.0)] = 0;
	ft_putstr_fd((char *)dec, b64->fd_out);
}

static int		valid_arg(t_parse *b64, char *arg, char *fname)
{
	int		tmp;

	if ((b64->fd_out == 1) && (!ft_strcmp(arg, "out") || !ft_strcmp(arg, "o")))
	{
		b64->flag |= F_OUT;
		if (!fname)
			ft_putstr_fd("missing argument for '-out'\n", 2);
		return (!fname ? 1 : 0);
	}
	else if (!ft_strcmp(arg, "in") || !ft_strcmp(arg, "i"))
	{
		b64->flag |= F_IN;
		if (!fname)
			ft_putstr_fd("missing argument for '-in'\n", 2);
		if (open_file_to_fd(&tmp, fname, 0))
			return (1);
		close(tmp);
	}
	else if (!ft_strcmp(arg, "d") || !ft_strcmp(arg, "-decode"))
		b64->flag |= D_FLAG;
	else if (!ft_strcmp(arg, "e") || !ft_strcmp(arg, "-encode"))
		b64->flag |= E_FLAG;
	else
		return (1);
	return (0);
}

int				parse_b64(char **av, t_parse *b64, t_ssl *ssl, int i)
{
	while ((av[++i]))
	{
		if (av[i][0] == '-')
		{
			if (valid_arg(b64, &av[i][1], av[i + 1]))
			{
				ssl->flag = b64->flag & F_IN ? -42 : ssl->flag;
				ssl->flag = b64->flag & F_OUT ? -42 : ssl->flag;
				return (ft_error(6, &av[i][1], ssl));
			}
			else if (b64->fd_out == 1 && b64->flag & F_OUT)
				open_file_to_fd((int*)&b64->fd_out, av[++i], 1);
			else if ((!b64->fd_in) && (b64->flag & F_IN))
				open_file_to_fd((int*)&b64->fd_in, av[++i], 0);
		}
		else
			return (ft_error(6, av[i], ssl));
	}
	return (0);
}
