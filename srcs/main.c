/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 06:11:57 by rpapagna          #+#    #+#             */
/*   Updated: 2019/11/22 20:45:32 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int				main(int ac, char **av)
{
	t_ssl	ssl;
	int		i;
	char	**tmp;

	ft_bzero(&ssl, (sizeof(t_ssl)));
	tmp = av;
	while (handle_inputs(&ac, &av, &ssl))
	{
		if (!ssl.stdin)
			break ;
		i = 0;
		while (i < ac)
		{
			ft_strdel(&av[i]);
			i++;
		}
		ft_memdel((void**)&av);
		ft_bzero(&ssl, (sizeof(t_ssl)));
		ac = 1;
		av = tmp;
	}
	DEBUG ? system("leaks ft_ssl") : 0;
	return (0);
}
