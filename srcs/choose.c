/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 23:45:13 by rpapagna          #+#    #+#             */
/*   Updated: 2019/10/06 16:13:11 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "encode.h"
#include "hash.h"
#include "standard.h"

void			ssl_md5(char **av, t_ssl *ssl)
{
	int		i;
	char	*line;

	i = -1;
	line = NULL;
	if (!(ssl->flag & 0x38000) && !ssl->flag && ssl->file_index[0])
		;
	else if (!(ssl->flag & S_FLAG) && (!*(ssl->fd) || ssl->flag & P_FLAG))
	{
		get_stdin(&line, 0, 1, 0);
		line = (!line) ? ft_strdup("") : line;
		ssl->flag &= ~0x40000;
		if (ssl->flag || (ssl->flag && !(ssl->flag & 0x10000)))
			ssl->flag |= 0x8000;
		hash(av[1], line, ssl, 0);
		ft_pipewrench("-s", &line) ? ssl->flag &= ~0x1000 : 0;
	}
	ssl->flag &= ~P_FLAG;
	while (ssl->fd[++i])
	{
		ssl->flag &= ~0x40000;
		hash(av[1], av[ssl->file_index[i]], ssl, i);
	}
}

void			ssl_b64(char **av, t_ssl *ssl)
{
	ft_printf("base64 done here\n");
	(void)av;
	(void)ssl;
}

void			ssl_des(char **av, t_ssl *ssl)
{
	ft_printf("[%s] you made it to the part where you decide how to dispatch\n",
	av[1]);
	(void)ssl;
}

void				ssl_standard(char **av, t_ssl *ssl)
{
	if (ssl->type == 41 && ft_printf("%s%s", VERSION, COPYRIGHT))
		;
	else if (ssl->type == 42)
		rand_command(av, ssl, 0);
	else if (ssl->type == 43 && opt_desciption(ssl->type))
		;
	(void)av;
}
