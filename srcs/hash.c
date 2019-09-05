/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 21:28:37 by rpapagna          #+#    #+#             */
/*   Updated: 2019/09/05 01:40:42 by rpapagna         ###   ########.fr       */
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

char			*get_hash(char **to_hash, char **input, t_ssl *ssl, int i)
{
	char		buf[PAGESIZE + 1];
	char		*tmp;
	char		*contents;
	static char	*(*hasher[5])(char *, char *) = {
				md5, sha224, sha256, sha384, sha512};

	ft_bzero(buf, PAGESIZE);
	*input = *to_hash;
	if (ssl->fd[i] > 2)
	{
		contents = "";
		while (read(ssl->fd[i], buf, PAGESIZE) > 0)
		{
			copy_free((char *)buf, &contents, &tmp);
			ft_bzero(buf, PAGESIZE);
		}
		copy_free((char*)buf, &contents, &tmp);
		*to_hash = ft_strdup(contents);
		free(contents);
		close(ssl->fd[i]);
	}
	else
		*to_hash = ft_strdup(*to_hash);
	return ((*hasher[ssl->type - 1])(buf, *to_hash));
}

void			hash(char *input, char *to_hash, t_ssl *ssl, int i)
{
	if ((!(ssl->flag & 0x18000) && (ssl->flag & 0x40000 || ssl->fd[i])
		&& !(ssl->flag & 0x20000)))
	{
		ft_printf("%s (", ft_strtoupper(input));
		IF_THEN(ssl->fd[i] < 1, ft_putchar('\"'));
		ft_printf("%s", to_hash);
		IF_THEN(ssl->fd[i] < 1, ft_putchar('\"'));
		ft_printf(") = ");
	}
	if (!(ssl->flag & 0x40000) && ssl->flag & 0x8000 && ssl->fd[i])
		ft_printf("%s", to_hash);
	ft_printf("%s%c", get_hash(&to_hash, &input, ssl, i),
	((!(ssl->flag & 0x20000) || ssl->flag & 0x10000 || ssl->flag & 0x40000)
	|| (ssl->flag & 0x20000 && !(ssl->flag & 0x10000) &&
	(ssl->flag & 0x8000)) ? '\n' : ' '));
	if (!(ssl->flag & 0x40000) && ssl->flag & 0x20000 && !(ssl->flag & 0x18000))
	{
		IF_THEN(ssl->fd[i] < 1, ft_putchar('\"'));
		IF_THEN((ssl->fd[i] || ssl->flag & 0x20000), ft_printf("%s", input));
		IF_THEN(ssl->fd[i] < 1, ft_putchar('\"'));
		ft_putchar('\n');
	}
	IF_THEN(ssl->flag & 0x8000 && ssl->fd[i], ft_putchar('\n'));
	ft_strdel(&to_hash);
}

char			dash_s(char **av, int *i, int *j, t_ssl *ssl)
{
	char	p_flag;

//	read_files(av, ssl, *i + 1, 0);
	p_flag = 0;
	if (ssl->flag & 0x8000)
		p_flag = 1;
	if (!(ssl->flag & 0x20000))
		ssl->flag |= 0x40000;
	if (av[*i][++(*j)])
	{
		ssl->flag &= ~0x8000;
		hash(av[1], &av[*i][*j], ssl, 0);
		if (p_flag)
			ssl->flag |= 0x8000;
		return (1);
	}
	if (av[++(*i)] && av[*i][0])
	{
		ssl->flag &= ~0x8000;
		hash(av[1], &av[*i][0], ssl, 0);
		if (p_flag)
			ssl->flag |= 0x8000;
		return (1);
	}
	return (0);
}
