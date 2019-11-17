/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 15:46:30 by rpapagna          #+#    #+#             */
/*   Updated: 2019/11/16 17:16:31 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENCODE_H
# define ENCODE_H


#include "ft_ssl.h"

/*
**	--------------------------------
**				MACROS
**	--------------------------------
*/

# define B_E "-e\t\tEncode input stream to Base64 (default)\n"
# define B_D "-d\t\tDecode incoming Base64 stream to binary data\n"
# define B_R "-r\t\tWrites encoded data as a continuous block to stdout\n"
# define D_A "-a\t\tDecode/encode the input/output in base64\n"
# define D_D "-d\t\tDecrypt mode\n"
# define D_E "-e\t\tEncrypt mode\n"
# define D_P "-p\t\tPassword in ascii is the next argument\n"
# define D_K "-k\t\tKey in hex is the next arguement\n"
# define D_S "-s\t\tSalt in hex is the next argument\n"
# define D_V "-v\t\tInitialization vector in hex is the next argument\n"

# define SEQUENCE '\x30'
# define INT '\x02'
# define V '\x01'
# define V1 '\xff'

/*
**	--------------------------------
**	    		STRUCTS
**	--------------------------------
*/

/*
**	--------------------------------
**	    		FUNCTIONS
**	--------------------------------
*/

void				des3(char *input, char *to_hash, t_ssl *ssl, int i);
void				des(char *input, char *to_hash, t_ssl *ssl, int i);
int					p_k_s_v(char **av, int *i, int *j, t_ssl *ssl);

void			    base64_nstr_fd(char *in, int len, int fd);

#endif
