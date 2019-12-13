/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   standard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:21:29 by rpapagna          #+#    #+#             */
/*   Updated: 2019/12/06 23:13:45 by rpapagna         ###   ########.fr       */
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

# define BITS 0x1
# define GEN 0x4
# define HEX 0x8

# define P_U "prime [-bits n] [-generate] [-hex] p\n"
# define P_B " -bits n\t\t\tNumber of bits in the generated prime number\n"
# define P_G " -generate\t\t\tGenerate a pseudo-random prime number\n"
# define P_H " -hex\t\t\t\tHexadecimal prime numbers (as output)\n"

void				prime_command(char **av, t_ssl *ssl);

#endif
