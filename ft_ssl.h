/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 06:12:54 by rpapagna          #+#    #+#             */
/*   Updated: 2019/10/31 23:37:17 by rpapagna         ###   ########.fr       */
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

# define A_FLAG 0x1
# define D_FLAG 0x8
# define E_FLAG 0x10
# define I_FLAG 0x100
# define K_FLAG 0x400
# define O_FLAG 0x4000
# define P_FLAG 0x8000
# define Q_FLAG 0x10000
# define R_FLAG 0x20000
# define S_FLAG 0x40000
# define V_FLAG 0x200000

# define VERBOSE 0
# define HELP_KEY 'h'
# define H_P "-p\techo STDIN to STDOUT and append the checksum to STDOUT\n"
# define H_Q "-q\tquiet mode\n"
# define H_R "-r\treverse the format of the output\n"
# define H_S "-s\tprint the sum of the given string\n"
# define B_D "-d\tdecode incoming Base64 stream to binary data\n"
# define B_R "-r\twrites encoded data as a continuous block to stdout\n"
# define D_A "-a\tdecode/encode the input/output in base64\n"
# define D_D "-d\tdecrypt mode\n"
# define D_E "-e\tencrypt mode\n"
# define D_P "-p\tpassword in ascii is the next argument\n"
# define D_K "-k\tkey in hex is the next arguement\n"
# define D_S "-s\tthe salt in hex is the next argument\n"
# define D_V "-v\tinitialization vector in hex is the next argument\n"
# define D_I "-i input_file\tWrite input to input_file\n"
# define D_O "-o output_file\tWrite output to output_file\n"
# define R_UI "-in file\t\tInput file\n"
# define R_UO "-out file\t\tOutput file\n"
# define R_UIK "-inkey file\t\tInput key\n"
# define R_UPI "-pubin\t\t\tInput is an RSA public\n"
# define R_UE "-encrypt\t\tEncrypt with public key\n"
# define R_UD "-decrypt\t\tDecrypt with private key\n"
# define R_UH "-hexdump\t\tHex dump output\n"
# define R_N "-noout\t\t\tDo not print encoded version of the key\n"
# define R_PI "-pubin\t\t\tExpect a public key (default private key)\n"
# define R_PO "-pubout\t\t\tOutput a public key (default private key)\n"
# define R_T "-text\t\t\tPrint in plain text in addition to encoded\n"

# ifdef _DEBUG_RULE_
#  define DEBUG 1
# else
#  define DEBUG 0
# endif
# define MAX_BIT_KEY 64

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

typedef struct		s_primary
{
	__uint64_t		d;
	__uint64_t		r;
	__uint64_t		x;
	__uint64_t		*a;
}					t_primary;

typedef struct		s_ssl
{
	int				flag;
	int				type;
	int				fd[255];
	int				file_index[255];
}					t_ssl;

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
void				rsa_text_out(t_rsa_out rsa, t_rsa gg);
__uint64_t			genrsa(t_rsa_out rsa);
int					ft_is_primary(__uint64_t number, float probability);
void				ssl_rsa(char **av, t_ssl *ssl);

void				des3(char *input, char *to_hash, t_ssl *ssl, int i);
void				des(char *input, char *to_hash, t_ssl *ssl, int i);
int					p_k_s_v(char **av, int *i, int *j, t_ssl *ssl);
void				ssl_des(char **av, t_ssl *ssl);

void				free_message(int count, __uint64_t **ptr);
void				sha64_cycle(int count, t_sha64bit *s, __uint64_t *w, int i);
void				sha64_start(char *to_hash, t_sha64bit *s);
void				sha32_cycle(int count, t_sha32bit *s, __uint32_t *w, int i);
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
