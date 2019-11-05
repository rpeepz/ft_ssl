/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:21:29 by rpapagna          #+#    #+#             */
/*   Updated: 2019/11/04 13:21:30 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RSA_H
# define RSA_H

#include "ft_ssl.h"

/*
**	--------------------------------
**				MACROS
**	--------------------------------
*/

# define MAX_BIT_KEY 64

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
void				rsa_encode_out(t_rsa_out rsa, t_rsa gg);
void				rsa_text_out(t_rsa_out rsa, t_rsa gg);
void				rsa_command(t_rsa_out rsa);
__uint64_t			genrsa(t_rsa_out rsa);
int					ft_is_primary(__uint64_t number, float probability);

#endif