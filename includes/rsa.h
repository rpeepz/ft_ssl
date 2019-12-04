/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:21:29 by rpapagna          #+#    #+#             */
/*   Updated: 2019/11/17 21:03:49 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RSA_H
# define RSA_H

# include "ft_ssl.h"

/*
**	--------------------------------
**				MACROS
**	--------------------------------
*/

# define MAX_BIT_KEY 64

# define F_OUT 0x1
# define F_IN 0x2
# define F_INK 0x4

# define R_TEXT 0x4
# define R_NOOUT 0x8
# define R_CHECK 0x10
# define R_PUBIN 0x20
# define R_PUBOUT 0x40
# define R_MODULUS 0x80
# define R_ENCRYPT 0x100
# define R_DECRYPT 0x200
# define R_HEXDUMP 0x400

# define R_B "numbits\t\tlength of key in bits\n"
# define R_UIK "-inkey file\tInput key\n"
# define R_UPI "-pubin\t\tInput is an RSA public key\n"
# define R_UE "-encrypt\tEncrypt with public key\n"
# define R_UD "-decrypt\tDecrypt with private key\n"
# define R_UH "-hexdump\tHex dump output\n"
# define R_N "-noout\t\tDo not print encoded version of the key\n"
# define R_PI "-pubin\t\tExpect a public key (default private key)\n"
# define R_PO "-pubout\t\tOutput a public key (default private key)\n"
# define R_T "-text\t\tPrint in plain text in addition to encoded\n"
# define R_MOD "-modulus\tPrint in hexadecimal the modulus\n"

# define PRIV_BEG "-----BEGIN RSA PRIVATE KEY-----\n"
# define PRIV_END "-----END RSA PRIVATE KEY-----\n"
# define PUB_BEG "-----BEGIN PUBLIC KEY-----\n"
# define PUB_END "-----END PUBLIC KEY-----\n"

# define EXPECT_PRV "Expecting: ANY PRIVATE KEY\n"
# define EXPECT_PUB "Expecting: PUBLIC KEY\n"

# define PKCS_1 "\xd\x6\x9\x2a\x86\x48\x86\xf7\xd\x1\x1\x1\5\xff"

/*
**	--------------------------------
**	    		STRUCTS
**	--------------------------------
*/

typedef struct		s_primary
{
	__uint64_t		d;
	__uint64_t		r;
	__uint64_t		x;
	__uint64_t		*a;
}					t_primary;

typedef struct		s_rsa_out
{
	int				flag;
	int				type;
	int				bits;
	int				fd_out;
	int				fd_in;
	int				fd_inkey;
}					t_rsa_out;

typedef struct		s_rsa
{
	__uint64_t		p;
	__uint64_t		q;
	__uint64_t		n;
	__uint64_t		phi;
	__uint64_t		dmp1;
	__uint64_t		dmq1;
	__uint64_t		iqmp;
	__uint64_t		e;
	__uint64_t		d;
}					t_rsa;

/*
**	--------------------------------
**	    		FUNCTIONS
**	--------------------------------
*/

void				debug_output(t_ssl *ssl, t_rsa_out rsa);

char				byte_len(__uint64_t n);
uint8_t				*byte_string(uint8_t *buf, __uint64_t n);
void				dump_to_buf(uint8_t *buf, char c, uint8_t *s, int *len);
void				asn1_pub(t_rsa gg, uint8_t *buf, uint8_t *buf2, int *len);
void				asn1(t_rsa gg, uint8_t *buf, uint8_t *buf2, int *len);

void				rsa_out_options(t_rsa_out rsa, t_rsa gg, char option);
void				rsa_encode_out(t_rsa_out rsa, t_rsa gg);
void				rsa_text_out(t_rsa_out rsa, t_rsa gg);
void				rsautl(t_rsa_out rsa, t_rsa gg);
t_rsa				rsa_command(t_rsa_out rsa);

__uint64_t			genrsa(t_rsa_out rsa);
int					ft_is_primary(__uint64_t number, float probability);

#endif
