/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 19:09:32 by rpapagna          #+#    #+#             */
/*   Updated: 2019/11/17 21:02:21 by rpapagna         ###   ########.fr       */
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
		if (rsa.flag & R_NOOUT)
			return ;
		else if (rsa.flag & R_CHECK)
			;
		else if (rsa.flag & R_PUBIN)
			decode(rsa, &gg, 1);
		else if (rsa.flag & R_TEXT)
			decode(rsa, &gg, 2);
		else if (rsa.flag & R_PUBOUT)
			decode(rsa, &gg, 3);
		rsa_text_out(rsa, gg);
	}
}
