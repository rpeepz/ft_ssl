/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cipher.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 15:46:30 by rpapagna          #+#    #+#             */
/*   Updated: 2019/12/18 16:55:41 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CIPHER_H
# define CIPHER_H

# include "ft_ssl.h"

/*
**	--------------------------------
**				MACROS
**	--------------------------------
*/

# define A_FLAG 0x4
# define D_FLAG 0x8
# define E_FLAG 0x10
# define D_PASS 0x10
# define D_KEY 0x20
# define D_SALT 0x40
# define D_VECT 0x80

# define B_U "base64 [-e | -d] [-in file] [-out file]\n"
# define B_E " -e\t\tEncode input stream to Base64 (default)\n"
# define B_D " -d\t\tDecode incoming Base64 stream to binary data\n"
# define D_A " -a\t\tDecode/encode the input/output in base64\n"
# define D_D " -d\t\tDecrypt mode\n"
# define D_E " -e\t\tEncrypt mode\n"
# define D_P " -p\t\tPassword in ascii is the next argument\n"
# define D_K " -k\t\tKey in hex is the next arguement\n"
# define D_S " -s\t\tSalt in hex is the next argument\n"
# define D_V " -v\t\tInitialization vector in hex is the next argument\n"

# define SEQUENCE '\x30'
# define BIT '\x03'
# define INT '\x02'
# define V '\x01'
# define V1 '\xff'

/*
**	--------------------------------
**	    		STRUCTS
**	--------------------------------
*/

typedef struct		s_parse
{
	int				fd_in;
	int				fd_out;
	uint8_t			flag:8;
	uint8_t			mode:4;
}					t_parse;

/*
**	--------------------------------
**	    		FUNCTIONS
**	--------------------------------
*/

void				des3(char *input, char *to_hash, t_ssl *ssl, int i);
void				des(char *input, char *to_hash, t_ssl *ssl, int i);
int					p_k_s_v(char **av, int *i, int *j, t_ssl *ssl);

int					base64_decode(uint8_t *enc, uint8_t *dec, int len);
void				decode_driver(t_parse *b64);
void				base64_nstr_fd(uint8_t *in, int len, int fd, int *count);

int					parse_b64(char**av, t_parse *b64, t_ssl *ssl, int i);

#endif