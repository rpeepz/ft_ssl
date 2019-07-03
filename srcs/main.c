/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 06:11:57 by rpapagna          #+#    #+#             */
/*   Updated: 2019/07/03 06:25:52 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

int				main(int ac, char **av)
{
	char	*line;

	IF_RETURN(ac < 2, write(1, USAGE, 53));
	line = NULL;
	if (get_next_line(0, &line) > 0)
	{
		;
	}
	else
		return (1);
	return (0);
}
