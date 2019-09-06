/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 23:45:13 by rpapagna          #+#    #+#             */
/*   Updated: 2019/09/05 01:40:42 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ssl.h"

void			ssl_md5(char **av, t_ssl *ssl)
{
	int		i;
	char	*line;

	i = -1;
	line = NULL;
	if (!(ssl->flag & 0x38000) && !ssl->flag && ssl->file_index)
		;
	else if ((((!ssl->flag && !*(ssl->fd)) || ssl->flag & 0x8000 ||
	(!*(ssl->fd) && ssl->flag & 0x20000)) || (ssl->type && !ssl->flag)) &&
	get_stdin(&line, 0, 1, 0))
	{
		if (!line)
			line = ft_strdup("");
		ssl->flag &= ~0x40000;
		if (ssl->flag || (ssl->flag && !(ssl->flag & 0x10000)))
			ssl->flag |= 0x8000;
		hash(av[1], line, ssl, 0);
		IF_THEN(ft_pipewrench("-s", line), ssl->flag &= ~0x1000);
	}
	while (ssl->fd[++i])
	{
		ssl->flag &= ~0x40000;
		hash(av[1], av[ssl->file_index + i], ssl, i);
	}
}

void			ssl_des(char **av, t_ssl *ssl)
{
	ft_printf("[%s]you made it to the part where you decide how to hash this\n",
	av[1]);
	ssl = 0;
}
