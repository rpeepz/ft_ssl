/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 19:09:32 by rpapagna          #+#    #+#             */
/*   Updated: 2019/11/03 19:09:34 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft_ssl.h"

void				decode(t_rsa_out rsa, t_rsa *gg, int mode)
{
	(void)rsa;
	(void)gg;
	(void)mode;
}

void				rsa_command(t_rsa_out rsa)
{
	t_rsa		gg;

	ft_bzero(&rsa, sizeof(t_rsa_out));
	ft_bzero(&gg, sizeof(t_rsa));
	if (rsa.flag & 0x2)
	{
		if (rsa.flag & 0x8) //noout
			return ;
		else if (rsa.flag & 0x10) //check
			;
		else if (rsa.flag & 0x20) //pubin
			decode(rsa, &gg, 1);
		else if (rsa.flag & 0x4) //text
			decode(rsa, &gg, 2);
		else if (rsa.flag & 0x40) //pubout
			decode(rsa, &gg, 3);
		rsa_text_out(rsa, gg);
	}
}
