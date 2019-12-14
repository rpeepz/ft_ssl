/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   standard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:21:29 by rpapagna          #+#    #+#             */
/*   Updated: 2019/12/14 02:25:47 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STANDARD_H
# define STANDARD_H

# include "rsa.h"

/*
**	--------------------------------
**				MACROS
**	--------------------------------
*/

# define P_BITS 0x1
# define RAND_BASE64 0x2
# define RAND_OUT 0x4
# define P_GEN 0x4
# define HEX 0x8

# define RAND_DIR "/dev/urandom"
# define E_MANY "too many arguments\n"

# define P_U "prime [-bits n] [-generate] [-hex] p\n"
# define P_B " -bits n\tNumber of bits in the generated prime number\n"
# define P_G " -generate\tGenerate a pseudo-random prime number\n"
# define P_H " -hex\t\tHexadecimal prime numbers (as output)\n"
# define SR_U "rand [-base64 | -hex] [-out file] num-bytes\n"
# define SR_B " -base64\tPerform base64 encoding on output\n"
# define SR_H " -hex\t\tHexadecimal output\n"
# define DG_U "dgst [options]\n"
# define DG_H " -hex\t\t Hex dump output\n"
# define DG_B " -binary\t Binary output\n"
# define DG_S " -sign\t file\t Sign digest using private key in file\n"
# define DG_V " -verify file\t Verify a signature using public key in file\n"
# define DG_P " -prverify file\t Verify a signature using private key in file\n"
# define DG_O " -out file\t Output file (default stdout)\n"
# define DG_SIG " -signature file Signature to verify\n"
# define DG_H1 " -md5\t\t To use the md5 message digest algorithm\n"
# define DG_H2 " -sha1\t\t To use the sha1 message digest algorithm\n"
# define DG_H3 " -sha224\t To use the sha224 message digest algorithm\n"
# define DG_H4 " -sha256\t To use the sha256 message digest algorithm\n"
# define DG_H5 " -sha384\t To use the sha384 message digest algorithm\n"
# define DG_H6 " -sha512\t To use the sha512 message digest algorithm\n"

/*
**	-whirlpool      to use the whirlpool message digest algorithm
**	^ potentially figure this out and add it
*/

__uint64_t			genrand(__uint64_t min, __uint64_t max);
void				rand_command(char **av, t_ssl *ssl, int bytes);
void				prime_command(char **av, t_ssl *ssl);

#endif
