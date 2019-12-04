/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reference.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 22:50:51 by rpapagna          #+#    #+#             */
/*   Updated: 2019/11/22 20:45:22 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int				valid_flags(t_ssl *ssl, char c)
{
	while (ssl->type)
	{
		if (ssl->type < 10 && (c == 'p' || c == 'q' || c == 'r' || c == 's'))
		{
			ssl->flag |= 1 << (c - 'a');
		}
		else if (ssl->type > 10 && ssl->type < 20 &&
		(c == 'd' || c == 'e' || c == 'i' || c == 'o'))
		{
			ssl->flag |= 1 << (c - 'a');
		}
		else if (ssl->type > 20 && ssl->type < 30 &&
		(c == 'a' || c == 'd' || c == 'e' || c == 'i' || c == 'k' ||
		c == 'o' || c == 'p' || c == 's' || c == 'v'))
		{
			ssl->flag |= 1 << (c - 'a');
		}
		else
			break ;
		return (0);
	}
	ft_error(4, &c, ssl);
	return (1);
}

int				scan_rsa(char *input)
{
	if (!ft_strcmp(input, "genrsa"))
		return (31);
	else if (!ft_strcmp(input, "rsautl"))
		return (32);
	else if (!ft_strcmp(input, "rsa"))
		return (33);
	else if (!ft_strcmp(input, "primep"))
		return (36);
	return (0);
}

int				scan_des(char *input)
{
	if (!ft_strcmp(input, "des3-ecb"))
		return (28);
	else if (!ft_strcmp(input, "des3-cbc"))
		return (27);
	else if (!ft_strcmp(input, "des3-ofb"))
		return (26);
	else if (!ft_strcmp(input, "des3"))
		return (25);
	else if (!ft_strcmp(input, "des-ecb"))
		return (24);
	else if (!ft_strcmp(input, "des-cbc"))
		return (23);
	else if (!ft_strcmp(input, "des-ofb"))
		return (22);
	else if (!ft_strcmp(input, "des"))
		return (21);
	return (scan_rsa(input));
}

int				valid_command(char *input, t_ssl *ssl)
{
	int		i;

	i = 0;
	while (input[i] && input[i] != ' ')
		i++;
	input[i] = '\0';
	if (!ft_strcmp(input, "md5\0"))
		ssl->type = 1;
	else if (!ft_strcmp(input, "sha224"))
		ssl->type = 2;
	else if (!ft_strcmp(input, "sha256"))
		ssl->type = 3;
	else if (!ft_strcmp(input, "sha384"))
		ssl->type = 4;
	else if (!ft_strcmp(input, "sha512"))
		ssl->type = 5;
	else if (!ft_strcmp(input, "base64"))
		ssl->type = 11;
	if (!ssl->type)
		ssl->type = scan_des(input);
	if (ssl->type)
		return (0);
	return (1);
}

/*
**	ft_printf("base64\ndes\tdes-ecb\t\tdes-cbc\t\tdes-ofb\n");
**	ft_printf("des3\tdes3-ecb\tdes3-cbc\tdes3-ofb\n");
*/

void			show_supported(void)
{
	ft_printf("%sStandard commands%s:\n", UWHT, NOCOL);
	ft_printf("genrsa\t\trsa\trsautl\n\n");
	ft_printf("%sMessage Digest Commands%s:\n", UWHT, NOCOL);
	ft_printf("md5\nsha224\t\tsha256\nsha384\t\tsha512\n\n");
	ft_printf("%sCipher Commands%s:\n", UWHT, NOCOL);
}
