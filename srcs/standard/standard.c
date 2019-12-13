/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   standard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 19:01:02 by rpapagna          #+#    #+#             */
/*   Updated: 2019/12/12 19:01:03 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"

void				ssl_standard(char **av, t_ssl *ssl)
{
	ft_printf("%s%s", VERSION, COPYRIGHT);
	if (ssl->type == 41)
		return ;
	(void)av;
}
