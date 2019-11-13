/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 19:09:32 by rpapagna          #+#    #+#             */
/*   Updated: 2019/11/13 14:39:13 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"

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
		//noout
		if (rsa.flag & 0x8)
			return ;
		//check
		else if (rsa.flag & 0x10)
			;
		//pubin
		else if (rsa.flag & 0x20)
			decode(rsa, &gg, 1);
		//text
		else if (rsa.flag & 0x4)
			decode(rsa, &gg, 2);
		//pubout
		else if (rsa.flag & 0x40)
			decode(rsa, &gg, 3);
		rsa_text_out(rsa, gg);
	}
}
