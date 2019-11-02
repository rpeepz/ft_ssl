/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 06:11:57 by rpapagna          #+#    #+#             */
/*   Updated: 2019/09/09 18:43:37 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ssl.h"

int				main(int ac, char **av)
{
	// int		i;
	// char	*line;
	t_ssl	ssl;

	// i = -1;
	// line = "";
	ft_bzero(&ssl, (sizeof(t_ssl)));
	if (handle_inputs(&ac, &av, &ssl))
	{
		;
	}
	return (0);
}
