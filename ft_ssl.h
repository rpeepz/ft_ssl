/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 06:12:54 by rpapagna          #+#    #+#             */
/*   Updated: 2019/09/05 01:40:42 by rpapagna         ###   ########.fr       */
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

# define VERBOSE 0
# define HELP_KEY 'h'
# define H_1 "-p\techo STDIN to STDOUT and append the checksum to STDOUT\n"
# define H_2 "-q\tquiet mode\n"
# define H_3 "-r\treverse the format of the output\n"
# define H_4 "-s\tprint the sum of the given string\n"
# define B_1 "-d\tdecode incoming Base64 stream to binary data\n"
# define B_2 "-r\twrites encoded data as a continuous block to stdout\n"
# define B_3 "-i input_file\tRead input from input_file\n"
# define B_4 "-o output_file\tWrite output to output_file\n"
# define D_1 "-a\tdecode/encode the input/output in base64\n"
# define D_2 "-d\tdecrypt mode\n"
# define D_3 "-e\tencrypt mode\n"
# define D_4 "-p\tpassword in ascii is the next argument\n"
# define D_5 "-k\tkey in hex is the next arguement\n"
# define D_6 "-s\tthe salt in hex is the next argument\n"
# define D_7 "-v\tinitialization vector in hex is the next argument\n"
# define D_8 "-i input_file\tWrite input to input_file\n"
# define D_9 "-o output_file\tWrite output to output_file\n"

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

typedef struct		s_ssl
{
	int				flag;
	int				type;
	int				fd[255];
	int				file_index;
}					t_ssl;

typedef struct		s_dispatch
{
	char			*(*hasher)(char *, char *);
}					t_dispatch;

/*
**	--------------------------------
**	    		FUNCTIONS
**	--------------------------------
*/

void				des3(char *input, char *to_hash, t_ssl *ssl, int i);
void				des(char *input, char *to_hash, t_ssl *ssl, int i);
int					p_k_s_v(char **av, int *i, int *j, t_ssl *ssl);
void				ssl_des(char **av, t_ssl *ssl);

void				free_message(int count, uint64_t **ptr);
void				sha64_cycle(int count, t_sha64bit *s, uint64_t *w, int i);
void				sha64_start(char *to_hash, t_sha64bit *s);
void				sha32_cycle(int count, t_sha32bit *s, uint32_t *w, int i);
void				sha32_set(char *to_hash, t_sha32bit *s);
char				*sha512(char *buf, char *to_hash);
char				*sha384(char *buf, char *to_hash);
char				*sha256(char *buf, char *to_hash);
char				*sha224(char *buf, char *to_hash);
char				*md5(char *buf, char *to_hash);
void				hash(char *input, char *to_hash, t_ssl *ssl, int i);
char				string_input(char **input, int *i, int *j, t_ssl *ssl);
void				ssl_md5(char **av, t_ssl *ssl);

int					get_stdin(char **line, char *str, int x, int i);
int					read_files(char **av, t_ssl *ssl, int i, int j);
int					valid_flags(t_ssl *ssl, char c);
int					valid_command(char *input, t_ssl *ssl);
int					handle_inputs(int *ac, char ***av, t_ssl *ssl);
int					ft_error(int err, char *ex, t_ssl *ssl);

/*
**	(COLORS)
*/

# define NOCOL "\e[;37m"
# define YEL "\e[0;33m"
# define UWHT "\e[4;37m"

#endif
