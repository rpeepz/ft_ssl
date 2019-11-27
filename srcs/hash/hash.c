/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 21:28:37 by rpapagna          #+#    #+#             */
/*   Updated: 2019/11/17 21:55:22 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"

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
	if ((!(ssl->flag & 0x38000) &&
	(ssl->flag & S_FLAG || (i >= 0 && ssl->fd[i]))))
	{
		ft_printf("%s (", ft_strtoupper(input));
		ssl->fd[i] < 1 ? ft_putchar('\"') : 0;
		ft_printf("%s", to_hash);
		ssl->fd[i] < 1 ? ft_putchar('\"') : 0;
		ft_printf(") = ");
	}
	!(ssl->flag & 0x70000) && (ssl->flag & P_FLAG || (ssl->fd[i] && ssl->flag))
	? ft_printf("%s", to_hash) : 0;
	ft_printf("%s%c", get_hash(&to_hash, &input, ssl, i),
	((!(ssl->flag & R_FLAG) || ssl->flag & Q_FLAG) || (ssl->flag & R_FLAG &&
	!(ssl->flag & Q_FLAG) && (ssl->flag & P_FLAG)) ? '\n' : ' '));
	if (ssl->flag & R_FLAG && !(ssl->flag & 0x18000))
	{
		ssl->fd[i] < 1 ? ft_putchar('\"') : 0;
		(ssl->fd[i] || ssl->flag & R_FLAG) ? ft_printf("%s", input) : 0;
		ssl->fd[i] < 1 ? ft_putchar('\"') : 0;
		ft_putchar('\n');
	}
	!ssl->fd[i] && !(ssl->flag & S_FLAG) ? ft_putchar('\n') : 0;
	ft_strdel(&to_hash);
}

char			string_input(char **av, int *i, int *j, t_ssl *ssl)
{
	char	p_flag;

	p_flag = 0;
	if (ssl->flag & P_FLAG)
		p_flag = 1;
	if (!(ssl->flag & R_FLAG))
		ssl->flag |= S_FLAG;
	if (av[*i][++(*j)])
	{
		ssl->flag &= ~P_FLAG;
		hash(av[1], &av[*i][*j], ssl, 0);
		if (p_flag)
			ssl->flag |= P_FLAG;
		return (1);
	}
	if (av[++(*i)] && av[*i][0])
	{
		ssl->flag &= ~P_FLAG;
		hash(av[1], &av[*i][0], ssl, 0);
		if (p_flag)
			ssl->flag |= P_FLAG;
		return (1);
	}
	return (0);
}
