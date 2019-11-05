/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 06:12:54 by rpapagna          #+#    #+#             */
/*   Updated: 2019/11/05 00:47:01 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "../libft/includes/libft.h"
# include <dirent.h>
# include <errno.h>
# include <math.h>

# ifdef _DEBUG_RULE_
#  define DEBUG 1
# else
#  define DEBUG 0
# endif

/*
**	--------------------------------
**				MACROS
**	--------------------------------
*/

# define VERBOSE 0
# define HELP_KEY 'h'
# define I_HELP "-in file\tInput file to read from\n"
# define O_HELP "-out file\tOutput file to write to\n"

/*
**	--------------------------------
**	    		STRUCTS
**	--------------------------------
*/

typedef struct		s_ssl
{
	int				flag;
	int				type;
	int				fd[255];
	int				file_index[255];
}					t_ssl;

/*
**	--------------------------------
**	    		FUNCTIONS
**	--------------------------------
*/

__uint64_t			mod_inverse(__uint64_t a, __uint64_t b);
__uint64_t			safe_modpow(__uint64_t b, __uint64_t c, __uint64_t mod);
__uint64_t			modpow(__uint64_t num, __uint64_t exp, __uint64_t mod);

void				ssl_rsa(char **av, t_ssl *ssl);
void				ssl_des(char **av, t_ssl *ssl);
void				ssl_md5(char **av, t_ssl *ssl);

void				free_message(int count, __uint64_t **ptr);
void				hash(char *input, char *to_hash, t_ssl *ssl, int i);
char				string_input(char **input, int *i, int *j, t_ssl *ssl);

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
