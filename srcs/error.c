/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 17:28:48 by rpapagna          #+#    #+#             */
/*   Updated: 2019/10/05 18:49:46 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ssl.h"

void			opt_desciption(int type)
{
	if (type < 10)
		ft_printf("\n%s%s%s%s", H_P, H_Q, H_R, H_S);
	else if (type == 11)
	{
		ft_printf("\n%s%s%s%s", B_D, B_R, D_I, D_O);
	}
	else if (type < 30)
	{
		ft_printf("\n%s%s%s%s%s", D_A, D_D, D_E, D_P, D_K);
		ft_printf("%s%s%s%s", D_S, D_V, D_I, D_O);
	}
}

void			show_supported(void)
{
	ft_printf("Standard commands:\n\n");
	ft_printf("%sMessage Digest Commands%s:\n", UWHT, NOCOL);
	ft_printf("md5\nsha224\t\tsha256\nsha384\t\tsha512\n\n");
	ft_printf("%sCipher Commands%s:\n", UWHT, NOCOL);
	ft_printf("base64\ndes\tdes-ecb\t\tdes-cbc\t\tdes-ofb\n");
	ft_printf("des3\tdes3-ecb\tdes3-cbc\tdes3-ofb\n");
}

void			full_usage(char *ex, int type)
{
	ft_printf("%susage%s: ", YEL, NOCOL);
	if (type < 10)
	{
		ft_printf("%s [-pqr] [-s string] [files ...]\n", ex);
	}
	else if (type == 11)
	{
		ft_printf("base64 [-d | -e] [-i input_file] [-o output_file]\n");
	}
	else if (type < 30)
	{
		ft_printf("%s [-a | -d | -e] [-p passwd] [-k key] [-s salt] ", ex);
		ft_printf("[-v vector] [-i input_file] [-o output_file]\n");
	}
}

int				ft_error(int err, char *ex, t_ssl *ssl)
{
	if (err == 1)
	{
		ft_printf("ft_ssl: Error: '%s' is an invalid command.\n", ex);
		ft_printf("usage: ft_ssl command [command opts] [command args]\n\n");
		show_supported();
	}
	if (err == 2)
	{
		ft_printf("Error: %s: option requires an argument -- %c\n",
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
		ft_printf("unknown option '-%c'\n", *ex);
	if (err == 5)
		ft_printf("ft_ssl: Error: %s need a flag\n", ex);
	return (err);
}
