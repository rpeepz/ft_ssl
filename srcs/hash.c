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

void			copy_free(char *buf, char **contents, char **tmp)
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
	char		buf[PAGESIZE + 1];
	char		*tmp;
	char		*contents;
	int			i;
	static char	*(*hasher[5])(char *, char *) = {
				md5, sha224, sha256, sha384, sha512};

	ft_bzero(buf, PAGESIZE);
	if (fd > 2)
	{
		contents = "";
		while (read(fd, buf, PAGESIZE) > 0)
		{
			copy_free((char *)buf, &contents, &tmp);
			ft_bzero(buf, PAGESIZE);
		}
		copy_free((char*)buf, &contents, &tmp);
		to_hash = contents;
		free(contents);
		close(fd);
	}
	mask_hashable(ft_strtolower(input), &mask);
	i = ((mask & 0xF00) >> 8) - 1;
	return ((*hasher[i])(buf, to_hash));
}

void			hash(char *input, char *to_hash, int fd, short mask)
{
	mask_hashable(input, &mask);
	if ((!(mask & 0x3000) && (mask & 0x8000 || fd) && !(mask & 0x4000)))
	{
		ft_printf("%s (", ft_strtoupper(input));
		IF_THEN(fd < 1, ft_putchar('\"'));
		ft_printf("%s", to_hash);
		IF_THEN(fd < 1, ft_putchar('\"'));
		ft_printf(") = ");
	}
	if (!(mask & 0x8000) && mask & 0x1000 && !fd)
		ft_printf("%s", to_hash);
	ft_printf("%s%c", get_hash(to_hash, input, mask, fd),
		((!(mask & 0x4000) || mask & 0x2000 || mask & 0x8000) ||
		(mask & 0x4000 && !(mask & 0x2000) && (mask & 0x1000)) ? '\n' : ' '));
	mask_hashable(input, &mask);
	if (!(mask & 0x8000) && mask & 0x4000 && !(mask & 0x3000))
	{
		IF_THEN(fd < 1, ft_putchar('\"'));
		IF_THEN((fd || mask & 0x4000), ft_printf("%s", to_hash));
		IF_THEN(fd < 1, ft_putchar('\"'));
		ft_putchar('\n');
	}
	IF_THEN(mask & 0x1000 && fd, ft_putchar('\n'));
}
