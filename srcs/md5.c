/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 21:28:37 by rpapagna          #+#    #+#             */
/*   Updated: 2019/08/08 23:56:49 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ssl.h"

int				hash(char *input, char *to_hash, int fd, short mask)
{
	IF_THEN(input[0] == 'm', mask |= 0x100);
	IF_THEN(!(mask & 0x100) && input[3] == '2', mask |= 0x200);
	if (!(mask & 0x100) && !(mask & 0x200) && input[3] == '5')
		mask |= 0x400;
	if (!fd)
		ft_printf("%s%.0d%.0d (\"%s\") = the hash\n", mask & 0x100 ?
		"MD5" : "SHA", mask & 0x200 ? 256 : 0, mask & 0x400 ? 512 : 0, to_hash);
	else
		ft_printf("%s%.0d%.0d (\"%d\") = the hash\n", mask & 0x100 ?
		"MD5" : "SHA", mask & 0x200 ? 256 : 0, mask & 0x400 ? 512 : 0, fd);
	return (0);
}
