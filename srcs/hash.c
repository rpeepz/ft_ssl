/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 21:28:37 by rpapagna          #+#    #+#             */
/*   Updated: 2019/08/10 04:15:50 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ssl.h"

char			*get_hash(char *to_hash, char *input, short mask, int fd)
{
	char	buf[32];
	char	*tmp;
	char	*contents;

	contents = "";
	if (fd > 2)
	{
		while (read(fd, buf, 31))
		{
			tmp = ft_strjoin(contents, buf);
			contents = tmp;
			free(tmp);
		}
		to_hash = contents;
		close(fd);
	}
	mask_hashable(ft_tolower_str(input), &mask);
	IF_RETURN(mask & 0x100, md5(to_hash));
	IF_RETURN(mask & 0x200, sha256(to_hash));
	IF_RETURN(mask & 0x400, sha512(to_hash));
	return ("custom(to_hash)");
}

int				hash(char *input, char *to_hash, int fd, short mask)
{
	mask_hashable(input, &mask);
	if ((!(mask & 0x3000) && (mask & 0x8000 || fd) && !(mask & 0x4000)))
	{
		ft_printf("%s (%c%s%c) = ", ft_toupper_str(input),
		fd < 1 ? '\"' : 0, to_hash, fd < 1 ? '\"' : 0);
	}
	if (!(mask & 0x8000) && mask & 0x1000 && !fd)
		ft_printf("%s\n", to_hash);
	ft_printf("%s%c", get_hash(to_hash, input, mask, fd),
		((!(mask & 0x4000) || mask & 0x2000 || mask & 0x8000) ||
		(mask & 0x4000 && !(mask & 0x2000) && (mask & 0x1000)) ? '\n' : ' '));
	if (!(mask & 0x8000) && mask & 0x4000 && !(mask & 0x3000))
		ft_printf("%c%s%c\n", fd < 1 ? '\"' : 0,
		(fd || mask & 0x4000) ? to_hash : "\0", fd < 1 ? '\"' : 0);
	ft_putchar(mask & 0x1000 && fd ? '\n' : 0);
	return (0);
}
