/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 06:11:57 by rpapagna          #+#    #+#             */
/*   Updated: 2020/02/03 14:20:07 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	frees necessary arguments for clean memory management
*/

int				clean_exit(int ac, char **av)
{
	int		i;

	i = 0;
	while (ac ? i < ac : av[i] != 0)
	{
		ft_strdel(&av[i]);
		i++;
	}
	ft_memdel((void**)&av);
	return (0);
}

/*
**	initialize main ssl struct and runs input loop
*/

int				main(int ac, char **av)
{
	t_ssl	ssl;
	char	**tmp;

	ft_bzero(&ssl, (sizeof(t_ssl)));
	tmp = av;
	while (handle_inputs(&ac, &av, &ssl))
	{
		if (!ssl.stdin)
			break ;
		clean_exit(ac, av);
		ft_bzero(&ssl, (sizeof(t_ssl)));
		ac = 1;
		av = tmp;
	}
	DEBUG ? system("leaks ft_ssl") : 0;
	return (0);
}
