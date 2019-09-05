/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 17:28:48 by rpapagna          #+#    #+#             */
/*   Updated: 2019/09/05 01:40:42 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ssl.h"

void			full_usage()
{
		ft_printf("%sStandard commands%s:\n\n", YEL, NOCOL);
		ft_printf("%sMessage Digest Commands%s:\n", UWHT, NOCOL);
		ft_printf("md5\nsha224\t\tsha256\nsha384\t\tsha512\n\n");
		ft_printf("%sCipher Commands%s:\n", UWHT, NOCOL);
		ft_printf("base64\ndes\tdes-ecb\t\tdes-cbc\t\tdes-ofb\n");
		ft_printf("des3\tdes3-ecb\tdes3-cbc\tdes3-ofb\n");
}

int				ft_error(int err, char *ex)
{
	if (err == 1)
	{
		ft_printf("ft_ssl: Error: '%s' is an invalid command.\n", ex);
		ft_printf("usage: ft_ssl command [command opts] [command args]\n\n");
		full_usage();
	}
	if (err == 2)
		ft_printf("ft_ssl: Error: %s: option requires an argument\n", ex);
	if (err == 3)
	{
		if (ex[0] == 'm')
			ft_printf("%susage%s: md5 [-pqr] [-s string] [files ...]\n", YEL,
			NOCOL);
		else
			ft_printf("options are\n%s%s%s%s", O_P, O_Q, O_R, O_S);
	}
	if (err == 4)
		ft_printf("unknown option '-%c'\n", *ex);
	if (err == 5)
		ft_printf("ft_ssl: Error: %s need a flag\n", ex);
	return (err);
}
