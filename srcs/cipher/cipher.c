/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cipher.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 22:52:45 by rpapagna          #+#    #+#             */
/*   Updated: 2019/12/18 21:16:39 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher.h"

int					p_k_s_v(char **av, int *i, int *j, t_ssl *ssl)
{
	if (av[*i][++(*j)])
	{
		ft_printf("will use '%s' as parameter of function '%c'\n",
		&av[*i][*j], av[*i][(*j) - 1]);
		return (1);
	}
	if (av[++(*i)] && av[*i][0])
	{
		ft_printf("will use '%s' as parameter of function '%c'\n",
		&av[*i][0], av[(*i) - 1][(*j) - 1]);
		return (1);
	}
	ssl->fd[104] = 0;
	return (0);
}

void				des_(char *input, char *to_hash, t_ssl *ssl, int i)
{
	ft_printf("des area\n");
	(void)input;
	(void)to_hash;
	(void)ssl;
	(void)i;
}

void				des3_(char *input, char *to_hash, t_ssl *ssl, int i)
{
	ft_printf("des3 area\n");
	(void)input;
	(void)to_hash;
	(void)ssl;
	(void)i;
}
