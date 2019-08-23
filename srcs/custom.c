/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 07:10:18 by rpapagna          #+#    #+#             */
/*   Updated: 2019/08/22 08:04:49 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ssl.h"

uint64_t		combiner(char *to_hash, int prime)
{
	int			tmp;
	int			len;
	char		*str;
	uint64_t	num;
	uint64_t	res;;

	tmp = 0;
	len = ft_strlen(to_hash);
	str = ft_strnew(8);
	res = 2;
	if (len > 7)
	{
		str = ft_strncpy(str, to_hash, 8);
		while (tmp < 8)
		{
			ft_printf("%c, %d, %d\n", str[tmp], prime, len / 2);
			num = pow((str[tmp] * prime), len / 2);
			ft_printf("num [%lli]\n", num);
			res += num;
			ft_printf("res [%lli]\n", res);
			tmp++;
		}
	}
	// while (tmp < len)
	// {
	// 	num = pow(to_hash[tmp], len);
	// }
	return tmp;
}

char			*custom(char *buf, char *to_hash)
{
	uint64_t	result;
	int			prime;

	prime = 280859;
	result = combiner(to_hash, prime);
	to_hash = buf;
	ft_sprintf(to_hash, "%x", result);
	return (to_hash);
}