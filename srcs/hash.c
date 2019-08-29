/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 21:28:37 by rpapagna          #+#    #+#             */
/*   Updated: 2019/08/28 01:57:49 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ssl.h"

void			do_this_thing(char *buf, char **contents, char **tmp)
{
	buf[PAGESIZE] = 0;
	*tmp = ft_strjoin(*contents, buf);
	if (ft_strcmp(*contents, ""))
		ft_strdel(contents);
	*contents = ft_strdup(*tmp);
	ft_strdel(tmp);
}

char			*get_hash(char *to_hash, char *input, short mask, int fd)
{
	char	buf[PAGESIZE + 1];
	char	*tmp;
	char	*contents;

	ft_bzero(buf, PAGESIZE);
	contents = "";
	if (fd > 2)
	{
		while (read(fd, buf, PAGESIZE) > 0)
		{
			do_this_thing((char *)buf, &contents, &tmp);
			ft_bzero(buf, PAGESIZE);
		}
		do_this_thing((char*)buf, &contents, &tmp);
		to_hash = contents;
		free(contents);
		close(fd);
	}
	mask_hashable(ft_strtolower(input), &mask);
	IF_RETURN(mask & 0x100, md5(buf, to_hash));
	IF_RETURN(mask & 0x200, sha256(buf, to_hash));
	IF_RETURN(mask & 0x400, sha512(buf, to_hash));
	return ("----No hash specified----");
}

int				hash(char *input, char *to_hash, int fd, short mask)
{
	mask_hashable(input, &mask);
	if ((!(mask & 0x3000) && (mask & 0x8000 || fd) && !(mask & 0x4000)))
	{
		ft_printf("%s (%c%s%c) = ", ft_strtoupper(input),
		fd < 1 ? '\"' : 0, to_hash, fd < 1 ? '\"' : 0);
	}
	if (!(mask & 0x8000) && mask & 0x1000 && !fd)
		ft_printf("%s", to_hash);
	ft_printf("%s%c", get_hash(to_hash, input, mask, fd),
		((!(mask & 0x4000) || mask & 0x2000 || mask & 0x8000) ||
		(mask & 0x4000 && !(mask & 0x2000) && (mask & 0x1000)) ? '\n' : ' '));
	mask_hashable(input, &mask);
	if (!(mask & 0x8000) && mask & 0x4000 && !(mask & 0x3000))
		ft_printf("%c%s%c\n", fd < 1 ? '\"' : 0,
		(fd || mask & 0x4000) ? to_hash : "\0", fd < 1 ? '\"' : 0);
	ft_putchar(mask & 0x1000 && fd ? '\n' : 0);
	return (0);
}
