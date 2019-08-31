/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 06:12:54 by rpapagna          #+#    #+#             */
/*   Updated: 2019/08/28 05:31:42 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "libft/includes/libft.h"
# include <dirent.h>
# include <errno.h>
# include <math.h>

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

# define O_P "-p\techo STDIN to STDOUT and append the checksum to STDOUT\n"
# define O_Q "-q\tquiet mode\n"
# define O_R "-r\treverse the format of the output\n"
# define O_S "-s\tprint the sum of the given string\n"

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
	uint32_t		hash[8];
	int				multiples;
	uint32_t		a;
	uint32_t		b;
	uint32_t		c;
	uint32_t		d;
	uint32_t		e;
	uint32_t		f;
	uint32_t		g;
	uint32_t		h;
	uint32_t		**message;
}					t_sha32bit;

typedef struct		s_sha64bit
{
	uint64_t		hash[8];
	int				multiples;
	uint64_t		a;
	uint64_t		b;
	uint64_t		c;
	uint64_t		d;
	uint64_t		e;
	uint64_t		f;
	uint64_t		g;
	uint64_t		h;
	uint64_t		**message;
}					t_sha64bit;

/*
**	--------------------------------
**	    		FUNCTIONS
**	--------------------------------
*/

int					ft_error(int err, char *ex);
int					get_stdin(char **line, char *str, int x, int i);
int					valid_hashable(char *input);
void				mask_hashable(char *input, short *mask);
void				free_message(int count, uint64_t **ptr);
short				loopdown(short mask, int i);
int					hash(char *input, char *to_hash, int fd, short mask);
char				*md5(char *buf, char *to_hash);
void				sha32_cycle(int count, t_sha32bit *s, uint32_t *w, int i);
void				sha32_set(char *to_hash, t_sha32bit *s);
char				*sha224(char *buf, char *to_hash);
char				*sha256(char *buf, char *to_hash);
void				sha64_cycle(int count, t_sha64bit *s, uint64_t *w, int i);
void				sha64_start(char *to_hash, t_sha64bit *s);
char				*sha384(char *buf, char *to_hash);
char				*sha512(char *buf, char *to_hash);

/*
**	(COLORS)
*/

# define NOCOL "\e[;37m"
# define YEL "\e[0;33m"
# define UWHT "\e[4;37m"

#endif
