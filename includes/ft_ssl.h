/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 06:12:54 by rpapagna          #+#    #+#             */
/*   Updated: 2019/12/13 17:19:21 by rpapagna         ###   ########.fr       */
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

# define VERSION "Ft_ssl, version 1.1b-release (x86_64-apple-darwin17)\n"
# define COPYRIGHT "Copyright (C) 2019 Robert Papagna MIT License\n"
# define VERBOSE 0
# define HELP_KEY 'h'
# define I_HELP " -in file\tInput file (default stdin)\n"
# define O_HELP " -out file\tOutput file (default stdout)\n"

/*
**	--------------------------------
**	    		STRUCTS
**	--------------------------------
*/

typedef struct		s_ssl
{
	int				stdin;
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
__uint64_t			mulmod(__uint64_t a, __uint64_t b, __uint64_t m);
__uint64_t			powmod(__uint64_t num, __uint64_t exp, __uint64_t mod);

void				ssl_standard(char **av, t_ssl *ssl);
void				ssl_rsa(char **av, t_ssl *ssl);
void				ssl_des(char **av, t_ssl *ssl);
void				ssl_md5(char **av, t_ssl *ssl);

int					clean_exit(int ac, char **av);
void				free_message(int count, __uint64_t **ptr);
void				hash(char *input, char *to_hash, t_ssl *ssl, int i);
char				string_input(char **input, int *i, int *j, t_ssl *ssl);

int					open_file_to_fd(int *fd, char *fname, int type);
int					get_stdin(char **line, char *str, int x, int i);
int					read_files(char **av, t_ssl *ssl, int i, int j);
int					valid_flags(t_ssl *ssl, char c);
int					valid_command(char *input, t_ssl *ssl);
void				show_supported(void);
int					handle_inputs(int *ac, char ***av, t_ssl *ssl);
int					opt_desciption(int type);
int					ft_error(int err, char *ex, t_ssl *ssl);

/*
**	(COLORS)
*/

# define NOCOL "\e[;37m"
# define YEL "\e[0;33m"
# define UWHT "\e[4;37m"

#endif
