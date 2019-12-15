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

void			copy_free(char *buf, char **acontents)
{
	char		*tmp;
	char		*contents;
	int			len;

	buf[PAGESIZE] = 0;
	tmp = NULL;
	contents = *acontents;
	tmp = ft_strjoin(contents, buf);
	len = ft_strlen(tmp);
	ft_strdel(&contents);
	contents = ft_strdup(tmp);
	ft_strdel(&tmp);
	*acontents = contents;
}

/*
**	TODO
**	streamline the effectivness of the following function.
**
**	Why?
**	The open file descriptor of a binary file cannot be properly hashed.
**	This is a problem for multiple reasons, one of which is the prevention
**	of accurate verrification of files and programs such as this program itself.
**
**	Current state:
**	--------------
**	The file descriptor is passed to this point where it is then read from
**	and its entire contents is stored in heap memory, which is passed to the
**	proper hash function and is padded and hashed.
**
**	The proposed fix:
**	-----------------
**	To continue passing file descriptor to the hash function itself to where
**	it can be safely read from and stored as blocks to be hashed.
*/

char			*get_hash(char **to_hash, char **input, t_ssl *ssl, int i)
{
	char		buf[PAGESIZE + 1];
	char		*contents;
	char		*tmp;
	static char	*(*hasher[6])(char *, char *) = {
				md5, sha224, sha256, sha384, sha512, sha1};

	ft_bzero(buf, PAGESIZE);
	contents = NULL;
	tmp = NULL;
	*input = *to_hash;
	if (ssl->fd[i] > 2)
	{
		contents = ft_strdup("");
		while (read(ssl->fd[i], buf, PAGESIZE) > 0)
		{
			copy_free(buf, &contents);
			ft_bzero(buf, PAGESIZE);
		}
		close(ssl->fd[i]);
		*to_hash = ft_strdup(contents);
		ft_strdel(&contents);
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
