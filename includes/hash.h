/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:20:59 by rpapagna          #+#    #+#             */
/*   Updated: 2019/11/17 21:35:30 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_H
# define HASH_H

# include "ft_ssl.h"

/*
**	--------------------------------
**				MACROS
**	--------------------------------
*/

# define RR_32(a, b) (((a) >> (b)) | ((a) << (32 - (b))))
# define E0_32(x) (RR_32(x, 2) ^ RR_32(x, 13) ^ RR_32(x, 22))
# define E1_32(x) (RR_32(x, 6) ^ RR_32(x, 11) ^ RR_32(x, 25))
# define S0_32(x) (RR_32(x, 7) ^ RR_32(x, 18) ^ ((x) >> 3))
# define S1_32(x) (RR_32(x, 17) ^ RR_32(x, 19) ^ ((x) >> 10))

# define RR(a, b) (((a) >> (b)) | ((a) << (64 - (b))))
# define E0(x) (RR(x, 28) ^ RR(x, 34) ^ RR(x, 39))
# define E1(x) (RR(x, 14) ^ RR(x, 18) ^ RR(x, 41))
# define S0(x) (RR(x, 1) ^ RR(x, 8) ^ ((x) >> 7))
# define S1(x) (RR(x, 19) ^ RR(x, 61) ^ ((x) >> 6))

# define P_FLAG 0x8000
# define Q_FLAG 0x10000
# define R_FLAG 0x20000
# define S_FLAG 0x40000

# define H_P "-p\tEcho stdin to stdout and append the checksum to stdout\n"
# define H_Q "-q\tQuiet mode\n"
# define H_R "-r\tReverse the format of the output\n"
# define H_S "-s\tPrint the sum of the given string\n"

/*
**	--------------------------------
**	    		STRUCTS
**	--------------------------------
*/

typedef struct		s_md5
{
	unsigned int	hash[4];
	unsigned int	multiples;
	unsigned int	a;
	unsigned int	b;
	unsigned int	c;
	unsigned int	d;
	unsigned int	bit;
	unsigned int	mod;
	unsigned char	*message;
	unsigned char	table[16][4];
}					t_md5;

typedef struct		s_sha32bit
{
	__uint32_t		hash[8];
	int				multiples;
	__uint32_t		a;
	__uint32_t		b;
	__uint32_t		c;
	__uint32_t		d;
	__uint32_t		e;
	__uint32_t		f;
	__uint32_t		g;
	__uint32_t		h;
	__uint32_t		**message;
}					t_sha32bit;

typedef struct		s_sha64bit
{
	__uint64_t		hash[8];
	int				multiples;
	__uint64_t		a;
	__uint64_t		b;
	__uint64_t		c;
	__uint64_t		d;
	__uint64_t		e;
	__uint64_t		f;
	__uint64_t		g;
	__uint64_t		h;
	__uint64_t		**message;
}					t_sha64bit;

void				sha64_cycle(int count, t_sha64bit *s, __uint64_t *w, int i);
void				sha64_start(char *to_hash, t_sha64bit *s);
void				sha32_cycle(int count, t_sha32bit *s, __uint32_t *w, int i);
void				sha32_set(char *to_hash, t_sha32bit *s);
char				*sha512(char *buf, char *to_hash);
char				*sha384(char *buf, char *to_hash);
char				*sha256(char *buf, char *to_hash);
char				*sha224(char *buf, char *to_hash);
char				*md5(char *buf, char *to_hash);

#endif
