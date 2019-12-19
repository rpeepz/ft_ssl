/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 17:28:48 by rpapagna          #+#    #+#             */
/*   Updated: 2019/12/18 23:52:21 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "cipher.h"
#include "hash.h"
#include "rsa.h"
#include "standard.h"
#include <stdio.h>

int				opt_desciption(int type)
{
	if (type < 10)
		dprintf(2, "%s%s%s%s", H_P, H_Q, H_R, H_S);
	else if (type == 11)
		dprintf(2, "%susage%s: %s%s%s%s%s", YEL, NOCOL, B_U,\
		B_E, B_D, I_HELP, O_HELP);
	else if (type < 30)
		;
	else if (type == 31)
		dprintf(2, "%s%s", O_HELP, R_B);
	else if (type == 32)
		dprintf(2, "%s%s%s%s%s%s%s", I_HELP, O_HELP, R_UIK,\
		R_UPI, R_UE, R_UD, R_UH);
	else if (type == 33)
		dprintf(2, "%s%s%s%s%s%s%s%s",\
		R_C, R_N, I_HELP, O_HELP, R_MOD, R_PI, R_PO, R_T);
	else if (type == 36)
		dprintf(2, "%susage%s: %s%s%s%s", YEL, NOCOL, P_U, P_B, P_G, P_H);
	else if (type == 42)
		dprintf(2, "%susage%s: %s%s%s%s", YEL, NOCOL, SR_U, SR_B, SR_H, O_HELP);
	else if (type == 43)
		dprintf(2, "%susage%s: %s%s%s%s%s%s%s%s%s%s%s%s%s%s", YEL, NOCOL, DG_U,\
		DG_H, DG_B, DG_S, DG_V, DG_P, DG_O, DG_SIG,\
		DG_H1, DG_H2, DG_H3, DG_H4, DG_H5, DG_H6);
	return (-1);
}

void			opt_des(int type)
{
	char	*s;

	s = "des3-ebc";
	s = type == 27 ? "des3-cbc" : s;
	s = type == 26 ? "des3-ofb" : s;
	s = type == 25 ? "des3" : s;
	s = type == 24 ? "des-ebc" : s;
	s = type == 23 ? "des-cbc" : s;
	s = type == 22 ? "des-ofb" : s;
	s = type == 21 ? "des" : s;
	dprintf(2, "%susage%s: %s\t[-e | -d | -a] [-in file]", YEL, NOCOL, s);
	dprintf(2, " [-out file]\n\t\t[-v IV] [-k key] [-p source] [-s salt]\n\n");
	dprintf(2, "%s%s%s%s%s%s%s%s%s", D_E, D_D, D_A, I_HELP, O_HELP,\
	D_V, D_K, D_P, D_S);
}

void			rsa_error(int e)
{
	if (e == 20)
		ft_putstr_fd("Only private keys can be checked\n", 2);
	if (e == 19)
		ft_putstr_fd("A private key is needed for this operation\n", 2);
	else
	{
		e > 22 ? ft_putstr_fd("no keyfile specified\n", 2) : 0;
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

void			ft_error2(int e, char *s, t_ssl *ssl)
{
	if (e != 6)
	{
		e > 20 && e < 23 ? ft_putstr_fd("RSA operation error\n", 2) : 0;
		if (e == 21 || e == 22)
		{
			ft_putstr_fd("RSA_padding_add_none:data too", 2);
			ft_putstr_fd(e % 2 ? " small " : " large ", 2);
			ft_putstr_fd("for key size\n", 2);
		}
		else
			rsa_error(e);
		return ;
	}
	else if (!(!ft_strcmp(s, "help") || !ft_strcmp(s, "h") ||\
	!ft_strcmp(s, "in") || !ft_strcmp(s, "inkey") || ssl->flag == -42))
		dprintf(2, "ft_ssl: Error: invalid option: \'%s\'\n", s);
	if (ssl->type == 31)
		dprintf(2, "%susage%s: genrsa [args] [numbits]\n", YEL, NOCOL);
	else if (ssl->type == 32)
		dprintf(2, "%susage%s: rsautl [options]\n", YEL, NOCOL);
	else if (ssl->type == 33)
		dprintf(2, "%susage%s: rsa [options]\n", YEL, NOCOL);
	ssl->type / 10 == 2 ? opt_des(ssl->type) : opt_desciption(ssl->type);
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
		dprintf(2, "%susage%s: %s [-pqr] [-s string] [files ...]\n",
		YEL, NOCOL, ex);
		if (ssl->flag || VERBOSE)
			opt_desciption(ssl->type);
	}
	if (err == 4 && *ex != 'h')
		dprintf(2, "unknown option '-%c'\n", *ex);
	if (err == 5)
		dprintf(2, "ft_ssl: Error: %s need a flag\n", ex);
	if (err >= 6)
		ft_error2(err, ex, ssl);
	return (!err ? 0 : -1);
}
