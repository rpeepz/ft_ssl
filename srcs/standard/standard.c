/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   standard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 19:01:02 by rpapagna          #+#    #+#             */
/*   Updated: 2019/12/14 02:25:14 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "standard.h"

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
