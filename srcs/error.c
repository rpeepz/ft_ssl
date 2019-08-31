/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 17:28:48 by rpapagna          #+#    #+#             */
/*   Updated: 2019/08/30 17:28:50 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ssl.h"

int				ft_error(int err, char *ex)
{
	if (err == 1)
		ft_printf("ft_ssl: Error: '%s' is an invalid command.\n\n%s\n",
		ex, MC);
	if (err == 2)
		ft_printf("%s%s", ex, SFLAG);
	if (err == 3 && ex[0] == 'm')
		ft_printf("%s", USAGEMD5);
	else
	{
		if (err == 3)
			ft_printf("options are\n%s%s%s%s", O_P, O_Q, O_R, O_S);
	}
	return (err);
}
