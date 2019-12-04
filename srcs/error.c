/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 17:28:48 by rpapagna          #+#    #+#             */
/*   Updated: 2019/11/04 19:28:36 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "encode.h"
#include "hash.h"
#include "rsa.h"
#include <stdio.h>

void			opt_desciption(int type)
{
	if (type < 10)
		dprintf(2, "\n%s%s%s%s", H_P, H_Q, H_R, H_S);
	else if (type == 11)
	{
		dprintf(2, "\n%s%s%s%s%s", B_E, B_D, B_R, I_HELP, O_HELP);
	}
	else if (type < 30)
	{
		dprintf(2, "\n%s%s%s%s%s", D_A, D_D, D_E, D_P, D_K);
		dprintf(2, "%s%s%s%s", D_S, D_V, I_HELP, O_HELP);
	}
	else if (type == 31)
		dprintf(2, "\n%s%s", O_HELP, R_B);
	else if (type == 32)
		dprintf(2, "\n%s%s%s%s%s%s%s", I_HELP, O_HELP, R_UIK,
		R_UPI, R_UE, R_UD, R_UH);
	else if (type == 33)
		dprintf(2, "\n%s%s%s%s%s%s%s",\
		R_N, I_HELP, O_HELP, R_MOD, R_PI, R_PO, R_T);
}

void			full_usage(char *ex, int type)
{
	dprintf(2, "%susage%s: ", YEL, NOCOL);
	if (type < 10)
	{
		dprintf(2, "%s [-pqr] [-s string] [files ...]\n", ex);
	}
	else if (type == 11)
	{
		dprintf(2, "base64 [-d | -e] [-in file] [-out file]\n");
	}
	else if (type < 30)
	{
		dprintf(2, "%s [-a | -d | -e] [-p passwd] [-k key] [-s salt] ", ex);
		dprintf(2, "[-v vector] [-in file] [-out file]\n");
	}
}

void			rsa_error2(int e)
{
	if (e == 20)
		ft_putstr_fd("Only private keys can be checked\n", 2);
	else
	{
		ft_putstr_fd("Unable to load", 2);
		ft_putstr_fd(e % 2 ? " Public " : " Private ", 2);
		ft_putstr_fd("Key\n", 2);
	}
	if (e <= 8)
		ft_putstr_fd("PEM routines:PEM_read_bio:bad base64 decode\n", 2);
	else if (e <= 10)
		ft_putstr_fd("PEM routines:PEM_read_bio:no start line\n", 2);
	else if (e <= 12)
		ft_putstr_fd("PEM routines:PEM_read_bio:bad end line\n", 2);
	else if (e <= 14)
		ft_putstr_fd("asn1 encoding routines:ASN1_CHECK_T:wrong tag\n", 2);
}

void			rsa_error(char *s, t_ssl *ssl, int e)
{
	if (e != 6)
	{
		ft_putstr_fd("RSA operation error\n", 2);
		if (e == 21 || e == 22)
		{
			ft_putstr_fd("RSA_padding_add_none:data too", 2);
			ft_putstr_fd(e % 2 ? " small " : " large ", 2);
			ft_putstr_fd("for key size\n", 2);
		}
		else
			rsa_error2(e);
		return ;
	}
	if (!(!ft_strcmp(s, "help") || !ft_strcmp(s, "h") || !ft_strcmp(s, "in") ||\
		!ft_strcmp(s, "inkey")))
		dprintf(2, "ft_ssl: Error: invalid option: \'%s\'\n", s);
	if (ssl->flag == 'Z' && ssl->type == 33)
		dprintf(2, "ft_ssl: Error: rsa: option requires an argument\n");
	else if (ssl->type == 31)
		dprintf(2, "%susage%s: genrsa [args] [numbits]\n", YEL, NOCOL);
	else if (ssl->type == 32)
		dprintf(2, "%susage%s: rsautl [options]\n", YEL, NOCOL);
	else if (ssl->type == 33)
		dprintf(2, "%susage%s: rsa [options]\n", YEL, NOCOL);
	opt_desciption(ssl->type);
}

int				ft_error(int err, char *ex, t_ssl *ssl)
{
	if (err == 1)
	{
		dprintf(2, "ft_ssl: Error: '%s' is an invalid command.\n\n", ex);
		show_supported();
	}
	if (err == 2)
	{
		dprintf(2, "Error: %s: option requires an argument -- %c\n",
		ex, ssl->flag);
		ssl->flag = 0;
	}
	if (err == 3)
	{
		full_usage(ex, ssl->type);
		if (ssl->flag || VERBOSE)
			opt_desciption(ssl->type);
	}
	if (err == 4 && *ex != 'h')
		dprintf(2, "unknown option '-%c'\n", *ex);
	if (err == 5)
		dprintf(2, "ft_ssl: Error: %s need a flag\n", ex);
	if (err >= 6)
		rsa_error(ex, ssl, err);
	return (err);
}
