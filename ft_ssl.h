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

# define RR(a, b) (((a) >> (b)) | ((a) << (64 - (b))))
# define E0(x) (RR(x, 28) ^ RR(x, 34) ^ RR(x, 39))
# define E1(x) (RR(x, 14) ^ RR(x, 18) ^ RR(x, 41))
# define S0(x) (RR(x, 1) ^ RR(x, 8) ^ ((x) >> 7))
# define S1(x) (RR(x, 19) ^ RR(x, 61) ^ ((x) >> 6))

# include "libft/includes/libft.h"
# include <dirent.h>
# include <errno.h>
# include <math.h>

/*
**	--------------------------------
**				MACROS
**	--------------------------------
*/

# define USAGE "usage: ft_ssl command [command opts] [command args]\n"
# define USAGEMD5 "usage: md5 [-pqr] [-s string] [files ...]\n"
# define SFLAG ": option requires an argument -- s\n"
# define SC "Standard commands:\n"
# define MC "Supported commands:\nmd5\t\tsha256\t\tbasic\n"
# define CC "Cipher commands:\n"
# define O_P "-p\techo STDIN to STDOUT and append the checksum to STDOUT\n"
# define O_Q "-q\tquiet mode\n"
# define O_R "-r\treverse the format of the output\n"
# define O_S "-s\tprint the sum of the given string\n"
# define SUPPORT "Supported Commands:\nmd5\nsha256\nsha512\n"

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

typedef struct		s_sha
{
	unsigned int	hash[8];
	unsigned int	multiples;
	unsigned int	a;
	unsigned int	b;
	unsigned int	c;
	unsigned int	d;
	unsigned int	e;
	unsigned int	f;
	unsigned int	g;
	unsigned int	h;
	unsigned char	*message;
	unsigned int	array[64];
}					t_sha;

typedef struct		s_sha512
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
}					t_sha512;

/*
**	--------------------------------
**	    		FUNCTIONS
**	--------------------------------
*/

int					ft_error(int err, char *ex);
int					get_stdin(char **line, char *str, int x, int i);
int					valid_hashable(char *input);
void				mask_hashable(char *input, short *mask);
short				loopdown(short mask, int i);
int					hash(char *input, char *to_hash, int fd, short mask);
char				*md5(char *buf, char *to_hash);
char				*custom(char *buf, char *to_hash);
char				*sha256(char *buf, char *to_hash);
char				*sha512(char *buf, char *to_hash);

/*
**	(COLORS)
*/

# define NOCOL "\e[;37m"

# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define WHT "\e[0;37m"

# define BRED "\e[1;31m"
# define BGRN "\e[1;32m"
# define BYEL "\e[1;33m"
# define BMAG "\e[1;35m"
# define BCYN "\e[1;36m"
# define BWHT "\e[1;37m"

# define URED "\e[4;31m"
# define UGRN "\e[4;32m"
# define UYEL "\e[4;33m"
# define UMAG "\e[4;35m"
# define UCYN "\e[4;36m"
# define UWHT "\e[4;37m"

#endif
