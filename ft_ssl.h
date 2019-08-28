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

# define USAGE "usage: ft_ssl command [command opts] [command args]\n"
# define USAGEMD5 "usage: md5 [-pqr] [-s string] [files ...]\n"
# define SFLAG ": option requires an argument -- s\n"
# define SC "Standard commands:\n"
# define MC "Message Digest commands:\nmd5\t\tsha256\t\tsha512\n"
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
	unsigned int	initial_a;
	unsigned int	initial_b;
	unsigned int	initial_c;
	unsigned int	initial_d;
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
/*
**	--------------------------------
**	    		FUNCTIONS
**	--------------------------------
*/

int					get_stdin(char **line, char *str, int x, int i);
int					valid_hashable(char *input);
short				loopdown(short mask, int i);
void				mask_hashable(char *input, short *mask);
int					hash(char *input, char *to_hash, int fd, short mask);
char				*md5(char *buf, char *to_hash);
char				*custom(char *buf, char *to_hash);
char				*sha256(char *to_hash);
char				*sha512(char *to_hash);
int					ft_error(int err, char *ex);

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
